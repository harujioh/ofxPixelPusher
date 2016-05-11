#pragma once

#include "ofMain.h"

#include "ofxPixelPusherUnit.h"
#include "ofxDeviceRegistry.h"
#include "DeviceRegistryEvent.h"

/**
 * PixelPusher
 */
class ofxPixelPusher {
   public:
    ofxPixelPusher();

    /**
     * PixelPusherの探索、信号送信を開始する
     */
    void start();

    /**
     * PixelPusherの情報が更新されたらよばれる
     */
    void updateDevice(ofxDeviceRegistry &deviceRegistry);

    /**
     * 指定のPixelPusherの指定ピクセルの色を設定
     */
    void setColor(int groupIndex, int controllerIndex, int ledIndex, ofColor color);

    /**
     * 指定のPixelPusherの指定ピクセルの色を設定
     */
    void setColor(int groupIndex, int controllerIndex, int ledIndex, int position, ofColor color);

   private:
    /**
     * PixelPusher探すインスタンス
     */
    ofxDeviceRegistry deviceRegistry;

    /**
     * 同期的に処理を行うようにロックをかける
     */
    std::mutex mtx;

    /**
     * PixelPusherを実際にコントロールするクラス
     */
    map<string, ofxPixelPusherUnit *> pusherUnits;
};