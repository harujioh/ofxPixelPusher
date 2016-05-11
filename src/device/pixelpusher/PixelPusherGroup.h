#pragma once

#include "PixelPusher.h"

/**
 * PixelPusherのグループ
 */
class PixelPusherGroup {
   public:
    /**
     * グループにPixelPusherを追加
     */
    void addPixelPisher(PixelPusher *pusher);

    /**
     * グループからPixelPusherを削除
     */
    void removePixelPisher(PixelPusher *pusher);

    /**
     * グループに所属するPixelPusherの数を取得
     */
    int size();

    /**
     * グループに所属するPixelPusherを取得
     */
    vector<PixelPusher *> getPixelPushers();

    /**
     * グループに所属するPixelPusherにつながっているLEDストリップを取得
     */
    vector<LedStrip *> getStrips();

   private:
    /**
     * グループに所属するPixelPusher
     */
    vector<PixelPusher *> pushers;
};