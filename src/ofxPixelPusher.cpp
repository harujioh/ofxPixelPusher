#include "ofxPixelPusher.h"

ofxPixelPusher::ofxPixelPusher() { deviceRegistry.addEventListener(this); }

void ofxPixelPusher::start() { deviceRegistry.start(); }

void ofxPixelPusher::setColor(int groupIndex, int controllerIndex, int ledIndex, ofColor color) {
    mtx.lock();

    for (auto it : pusherUnits) {
        ofxPixelPusherUnit *pusherUnit = it.second;
        if (pusherUnit->isInGroup(groupIndex, controllerIndex)) {
            pusherUnit->setColor(ledIndex, color);
        }
    }

    mtx.unlock();
}

void ofxPixelPusher::setColor(int groupIndex, int controllerIndex, int ledIndex, int position, ofColor color) {
    mtx.lock();

    for (auto it : pusherUnits) {
        ofxPixelPusherUnit *pusherUnit = it.second;
        if (pusherUnit->isInGroup(groupIndex, controllerIndex)) {
            pusherUnit->setColor(ledIndex, position, color);
        }
    }

    mtx.unlock();
}

void ofxPixelPusher::updateDevice(ofxDeviceRegistry &deviceRegistry) {
    mtx.lock();

    map<string, PixelPusher *> pusherMap = deviceRegistry.getPixelPusherMap();
    for (auto it = pusherUnits.begin(); it != pusherUnits.end();) {
        if (pusherMap.count(it->first) == 0) {
            delete it->second;
            pusherUnits.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = pusherMap.begin(); it != pusherMap.end(); ++it) {
        if (pusherUnits.count(it->first) > 0) {
            pusherUnits[it->first]->updatePixelPusher(it->second);
        } else {
            pusherUnits[it->first] = new ofxPixelPusherUnit(it->second);
            pusherUnits[it->first]->start();
        }
    }

    mtx.unlock();
}