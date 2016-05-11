#include "ofxPixelPusherUnit.h"

ofxPixelPusherUnit::ofxPixelPusherUnit(PixelPusher *pusher) {
    updatePixelPusher(pusher);

    if (100 < pusher->updatePeriod && pusher->updatePeriod < 1000000) {
        sleepTime = (pusher->updatePeriod / 1000) + 1;
    }
}

ofxPixelPusherUnit::~ofxPixelPusherUnit() {
    stopThread();
    while (isThreadRunning())
        ;

    udp.Close();
}

void ofxPixelPusherUnit::updatePixelPusher(PixelPusher *pusher) {
    if (lock()) {
        this->pusher = pusher;
        unlock();
    }
}

void ofxPixelPusherUnit::start() {
    udp.Create();
    udp.Connect(pusher->getIpAddress().c_str(), SEND_PORT);

    ofThread::startThread();
}

void ofxPixelPusherUnit::threadedFunction() {
    while (isThreadRunning()) {
        if (lock()) {
            threadedUpdate();
            unlock();
            sleep(sleepTime);
        }
    }
}

void ofxPixelPusherUnit::threadedUpdate() {
    vector<uint8_t> *packet = pusher->serialize();
    if (packet->size() > 0) {
        if (100 < pusher->updatePeriod && pusher->updatePeriod < 1000000) {
            sleepTime = (pusher->updatePeriod / 1000) + 1;
        }

        uint8_t buf[packet->size()];
        for (int i = 0; i < packet->size(); i++) {
            buf[i] = (*packet)[i];
        }

        udp.Send((const char *)buf, packet->size());
    }
}

bool ofxPixelPusherUnit::isInGroup(int groupIndex, int controllerIndex) {
    if (pusher->groupOrdinal != groupIndex) {
        return false;
    }
    if (controllerIndex < 0) {
        return true;
    }
    return pusher->controllerOrdinal == controllerIndex;
}

void ofxPixelPusherUnit::setColor(int index, ofColor color) {
    if (index < pusher->getStripLength()) {
        pusher->getStrips()[index]->setPixel(color.getHex());
    }
}

void ofxPixelPusherUnit::setColor(int index, int position, ofColor color) {
    if (index < pusher->getStripLength()) {
        pusher->getStrips()[index]->setPixel(position, color.getHex());
    }
}
