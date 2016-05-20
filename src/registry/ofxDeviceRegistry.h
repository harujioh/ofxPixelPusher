#pragma once

#include "ofMain.h"
#include "ofxUDPManager.h"

#include "DeviceRegistryListener.h"
#include "DeviceHeader.h"
#include "PixelPusher.h"
#include "PixelPusherGroup.h"

/**
 * PixelPusher探して、見つかったら通知イベントを発火するクラス
 */
class ofxDeviceRegistry : public ofThread {
   public:
    ofxDeviceRegistry();
    ~ofxDeviceRegistry();

    /**
     * PixelPusher探索スタート
     */
    template <class T>
    void addEventListener(T *parent) {
        ofAddListener(listener.updateDevice, parent, &T::updateDevice);
    }

    /**
     * PixelPusher探索スタート
     */
    void start();

    /**
     * ofThreadのmain
     */
    void threadedFunction();

    /**
     * PixelPusherを取得
     */
    map<string, PixelPusher *> getPixelPusherMap();

    /**
     * 指定グループのPixelPusherを取得
     */
    vector<PixelPusher *> getPixelPushers(int groupIndex);

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
     * 待機時間
     */
    const int THREAD_INTERVAL = 100;

    /**
     * UDPで開くポート
     */
    const int DISCOVERY_PORT = 7331;

    /**
     * UDPで受信するバッファサイズ
     */
    const int BUFFER_SIZE = 1024;
    
    /**
     * スレッドの生存フラグ
     */
    bool alive = false;

    /**
     * PixelPusherが見つかったイベントの通知用インスタンス
     */
    DeviceRegistryListener listener;

    /**
     * 同期的に処理を行うようにロックをかける
     */
    std::mutex mtx;

    /**
     * UDP受信インスタンス
     */
    ofxUDPManager udp;

    /**
     * MACアドレスとPixelPusherポインタのmap
     */
    vector<PixelPusher *> pushers;

    /**
     * MACアドレスとPixelPusherポインタのmap
     * 同じPixelPusherで設定値が変更されたかチェックする用
     */
    map<string, PixelPusher *> pusherMap;

    /**
     * MACアドレスとPixelPusherが見つかった時のElapsedTimeのmap
     * PixelPusherがタイムアウトした場合に削除する用
     */
    map<string, uint64_t> pusherLastSeenMap;

    /**
     * グループIDとPixelPusherポインタのmap
     */
    map<int, PixelPusherGroup *> groupMap;

    /**
     * ofThread::start
     */
    void startThread();

    /**
     * ofThreadがまわっているときに呼ばれるupdateメソッド
     */
    void threadedUpdate();

    /**
     * 新しいPixelPusherが見つかった際に、登録する
     */
    void addNewPixelPusher(string macAddress, PixelPusher *pixelPusher);

    /**
     * PixelPusherのプロパティを更新する
     */
    void updatePixelPusher(string macAddress, PixelPusher *pixelPusher);
};