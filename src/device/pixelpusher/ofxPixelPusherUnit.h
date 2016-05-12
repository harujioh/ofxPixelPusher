#pragma once

#include "ofMain.h"
#include "ofxUDPManager.h"

#include "PixelPusher.h"

/**
 * PixelPusherに値を非同期送信するクラス
 */
class ofxPixelPusherUnit : public ofThread {
   public:
    ofxPixelPusherUnit(PixelPusher *pusher);
    ~ofxPixelPusherUnit();

    /**
     * PixelPusherインスタンスを更新
     */
    void updatePixelPusher(PixelPusher *pusher);

    /**
     * PixelPusherの非同期信号送信を開始する
     */
    void start();

    /**
     * ofThreadのmain
     */
    void threadedFunction();

    /**
     * つながっているLEDストリップの数を取得
     */
    int getStripLength();

    /**
     * 1本あたりのLEDの数を取得
     */
    int getPixelLength();

    /**
     * 特定のPixelPusherかチェックする
     */
    bool isInGroup(int groupIndex, int controllerIndex = -1);

    /**
     * LEDの色を変更
     */
    void setColor(int index, ofColor color);

    /**
     * LEDの色を変更
     */
    void setColor(int index, int position, ofColor color);

   private:
    /**
     * UDP送信ポート
     */
    const int SEND_PORT = 9897;

    /**
     * PixelPusherのパラメータに応じた待機時間
     */
    int sleepTime = 4;

    /**
     * PixelPusherインスタンス
     */
    PixelPusher *pusher;

    /**
     * UDP送信インスタンス
     */
    ofxUDPManager udp;

    /**
     * ofThreadのmain
     */
    void threadedUpdate();
};