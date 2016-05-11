#include "PixelPusherGroup.h"

void PixelPusherGroup::addPixelPisher(PixelPusher *pusher) {
    pushers.push_back(pusher);
    sort(pushers.begin(), pushers.end());
}

void PixelPusherGroup::removePixelPisher(PixelPusher *pusher) {
    pushers.erase(remove(pushers.begin(), pushers.end(), pusher), pushers.end());
    sort(pushers.begin(), pushers.end());
}

int PixelPusherGroup::size() { return pushers.size(); }

vector<PixelPusher *> PixelPusherGroup::getPixelPushers() { return pushers; }

vector<LedStrip *> PixelPusherGroup::getStrips() {
    vector<LedStrip *> strips;
    for (PixelPusher *pusher : pushers) {
        for (LedStrip *string : pusher->getStrips()) {
            strips.push_back(string);
        }
    }
    return strips;
}