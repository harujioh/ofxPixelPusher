#pragma once

#include "Device.h"
#include "LedStrip.h"

/**
 * PixelPusher
 */
class PixelPusher : public Device {
   public:
    PixelPusher(DeviceHeader header) throw(string);
    ~PixelPusher();

    bool operator<(const PixelPusher &obj) const;
    bool operator>(const PixelPusher &obj) const;
    bool operator==(const PixelPusher &obj) const;
    bool operator!=(const PixelPusher &obj) const;

    /**
     * プロパティを更新
     */
    void updateProperty(PixelPusher *pusher);

    /**
     * つながっているLEDストリップの数を取得
     */
    int getStripLength();

    /**
     * 1本あたりのLEDの数を取得
     */
    int getPixelLength();

    /**
     * つながっているLEDストリップを取得
     */
    vector<LedStrip *> getStrips();

    /**
     * シリアライズする
     */
    vector<uint8_t> *serialize();

    /**
     * 文字列として取得する
     */
    string str();

    /**
     * 接続可能なLEDの本数
     */
    uint8_t stripsAttached;

    /**
     * 1パケットに送信できるLEDの本数
     */
    uint8_t maxStripsPerPacket;

    /**
     * LED1本に対するLEDの数
     */
    uint16_t pixelsPerStrip;

    /**
     * 更新間隔(micro sec)
     */
    uint32_t updatePeriod;

    /**
     * PWMユニットの数
     */
    uint32_t powerTotal;

    /**
     * difference between received and expected sequence numbers
     */
    uint32_t deltaSequence;

    /**
     * コントローラのグループナンバー(設定値)
     */
    int32_t groupOrdinal;

    /**
     * コントローラのオーダーナンバー(設定値)
     */
    int32_t controllerOrdinal;

   private:
    /**
     * ボディに使用されるパケット長
     * uint8_t stripsAttached
     * uint8_t maxStripsPerPacket
     * uint16_t pixelsPerStrip
     * uint32_t updatePeriod
     * uint32_t powerTotal
     * uint32_t deltaSequence
     * int32_t controllerOrdinal
     * int32_t groupOrdinal
     */
    const int bodyLength = 24;

    /**
     * パケットに付与するindex番号
     */
    uint32_t packetNumber = 0;

    /**
     * テープLED
     */
    vector<LedStrip *> strips;

    /**
     * シリアライズされたパケット
     */
    vector<uint8_t> packet;
};