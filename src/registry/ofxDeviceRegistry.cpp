#include "ofxDeviceRegistry.h"

ofxDeviceRegistry::ofxDeviceRegistry() {}

ofxDeviceRegistry::~ofxDeviceRegistry() {
    mtx.lock();
    stopThread();
    while (isThreadRunning())
        ;
    mtx.unlock();

    for (PixelPusher *pusher : pushers) {
        delete pusher;
    }
    for (auto it : groupMap) {
        delete it.second;
    }

    udp.Close();
}

void ofxDeviceRegistry::start() {
    udp.Create();
    udp.Bind(DISCOVERY_PORT);
    udp.SetNonBlocking(true);

    ofThread::startThread();
}

void ofxDeviceRegistry::threadedFunction() {
    while (isThreadRunning()) {
        if (lock()) {
            threadedUpdate();
            unlock();
            sleep(THREAD_INTERVAL);
        }
    }
}

map<string, PixelPusher *> ofxDeviceRegistry::getPixelPusherMap() { return pusherMap; }

vector<PixelPusher *> ofxDeviceRegistry::getPixelPushers(int groupIndex) {
    if (groupMap.count(groupIndex) > 0) {
        return groupMap[groupIndex]->getPixelPushers();
    }
    vector<PixelPusher *> pixelPushers;
    return pixelPushers;
}

vector<LedStrip *> ofxDeviceRegistry::getStrips() {
    mtx.lock();
    vector<LedStrip *> strips;
    for (PixelPusher *pusher : pushers) {
        vector<LedStrip *> addStrips = pusher->getStrips();
        strips.insert(strips.end(), addStrips.begin(), addStrips.end());
    }
    mtx.unlock();
    return strips;
}

vector<LedStrip *> ofxDeviceRegistry::getStrips(int groupIndex) {
    vector<LedStrip *> strips;
    mtx.lock();
    if (groupMap.count(groupIndex) > 0) {
        vector<LedStrip *> addStrips = groupMap[groupIndex]->getStrips();
        strips.insert(strips.end(), addStrips.begin(), addStrips.end());
    }
    mtx.unlock();
    return strips;
}

void ofxDeviceRegistry::threadedUpdate() {
    char buf[BUFFER_SIZE];
    int size = udp.Receive(buf, BUFFER_SIZE);

    if (size > 0) {
        try {
            DeviceHeader header((uint8_t *)buf, size);
            header.parse();

            if (header.deviceType != DeviceDiscovery::PIXELPUSHER) {
                throw string("Ignoring non-PixelPusher discovery packet from : " + header.str());
            }

            PixelPusher *pixelPusher = new PixelPusher(header);
            string macAddress = pixelPusher->getMacAddress();
            pusherLastSeenMap[macAddress] = ofGetElapsedTimeMillis();
            if (pusherMap.count(macAddress) == 0) {
                addNewPixelPusher(macAddress, pixelPusher);
            } else {
                updatePixelPusher(macAddress, pixelPusher);
                delete pixelPusher;
            }
        } catch (string e) {
            ofLogError() << e;
        }
    }
}

void ofxDeviceRegistry::addNewPixelPusher(string macAddress, PixelPusher *pixelPusher) {
    mtx.lock();

    ofLogNotice("ofxDeviceRegistry::addNewPixelPusher") << "{\"header\":" << pixelPusher->getHeaderDescription() << ",\"body\":" << pixelPusher->str() << "}";
    pushers.push_back(pixelPusher);
    sort(pushers.begin(), pushers.end());

    pusherMap.insert(make_pair(macAddress, pixelPusher));

    int groupIndex = pixelPusher->groupOrdinal;
    if (groupMap.count(groupIndex) == 0) {
        groupMap.insert(make_pair(groupIndex, new PixelPusherGroup()));
    }
    groupMap[groupIndex]->addPixelPisher(pixelPusher);
    mtx.unlock();

    ofNotifyEvent(listener.updateDevice, *this);
}

void ofxDeviceRegistry::updatePixelPusher(string macAddress, PixelPusher *pixelPusher) {
    mtx.lock();

    ofLogVerbose("ofxDeviceRegistry::updatePixelPusher") << "{\"header\":" << pixelPusher->getHeaderDescription() << ",\"body\":" << pixelPusher->str() << "}";
    pusherMap[macAddress]->updateProperty(pixelPusher);

    mtx.unlock();

    ofNotifyEvent(listener.updateDevice, *this);
}