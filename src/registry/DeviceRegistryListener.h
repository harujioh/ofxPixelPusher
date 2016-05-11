#pragma once

class ofxDeviceRegistry;

/**
 * 新たなデバイスが見つかったり、デバイスが更新されたことを通知するリスナ
 */
class DeviceRegistryListener {
   public:
    /**
     * 新たなデバイスが見つかったり、デバイスが更新されたときに呼ばれるイベント
     */
    ofEvent<ofxDeviceRegistry> updateDevice;
};