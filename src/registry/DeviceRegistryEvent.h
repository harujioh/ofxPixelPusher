#pragma once

#include "ofxDeviceRegistry.h"

class ofxDeviceRegistry;
class LedStrip;

/**
 * PixelPusher探して、見つかったときに通知するクラス
 */
class DeviceRegistryEvent {
   public:
    DeviceRegistryEvent(ofxDeviceRegistry *deviceRegistry) : deviceRegistry(deviceRegistry) {}

    /**
     * LEDテープを取得
     */
    vector<LedStrip *> getStrips();

    /**
     * 指定グループのLEDテープを取得
     */
    vector<LedStrip *> getStrips(int groupIndex);

   private:
    /**
     * 実クラス
     */
    ofxDeviceRegistry *deviceRegistry = NULL;
};