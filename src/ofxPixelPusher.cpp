#include "ofxPixelPusher.h"

ofxPixelPusher::ofxPixelPusher() { deviceRegistry.addEventListener(this); }

void ofxPixelPusher::start() { deviceRegistry.start(); }

void ofxPixelPusher::setColor(ofColor color, float rate) {
    mtx.lock();

    color = getColor(color, rate);
    for (auto it : pusherUnits) {
        ofxPixelPusherUnit *pusherUnit = it.second;
        for (int ledIndex = 0; ledIndex < 8; ledIndex++) {
            pusherUnit->setColor(ledIndex, color);
        }
    }

    mtx.unlock();
}

void ofxPixelPusher::setColor(int ledIndex, ofColor color, float rate) {
    mtx.lock();

    color = getColor(color, rate);
    for (auto it : pusherUnits) {
        ofxPixelPusherUnit *pusherUnit = it.second;
        pusherUnit->setColor(ledIndex, color);
    }

    mtx.unlock();
}

void ofxPixelPusher::setColor(int groupIndex, int controllerIndex, int ledIndex, ofColor color, float rate) {
    mtx.lock();

    color = getColor(color, rate);
    for (auto it : pusherUnits) {
        ofxPixelPusherUnit *pusherUnit = it.second;
        if (pusherUnit->isInGroup(groupIndex, controllerIndex)) {
            pusherUnit->setColor(ledIndex, color);
        }
    }

    mtx.unlock();
}

void ofxPixelPusher::setColor(int groupIndex, int controllerIndex, int ledIndex, int position, ofColor color, float rate) {
    mtx.lock();

    color = getColor(color, rate);
    for (auto it : pusherUnits) {
        ofxPixelPusherUnit *pusherUnit = it.second;
        if (pusherUnit->isInGroup(groupIndex, controllerIndex)) {
            pusherUnit->setColor(ledIndex, position, color);
        }
    }

    mtx.unlock();
}

void ofxPixelPusher::setColor(int groupIndex, int controllerIndex, int ledIndex, vector<ofColor> &colors, float rate) {
    mtx.lock();

    for (auto it : pusherUnits) {
        ofxPixelPusherUnit *pusherUnit = it.second;
        if (pusherUnit->isInGroup(groupIndex, controllerIndex)) {
            for (int i = 0, l = MIN(colors.size(), pusherUnit->getPixelLength()); i < l; i++) {
                pusherUnit->setColor(ledIndex, i, getColor(colors[i], rate));
            }
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

ofColor ofxPixelPusher::getColor(ofColor color, float rate) {
    if (rate <= 0) {
        return ofColor::black;
    }
    if (rate >= 1) {
        return color;
    }

    int r = (float)color.r * rate;
    int g = (float)color.g * rate;
    int b = (float)color.b * rate;
    return ofColor(r, g, b);
}