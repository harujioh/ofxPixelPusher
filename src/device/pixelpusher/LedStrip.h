#pragma once

#include <iostream>
#include <vector>

#include "LedPixel.h"

using namespace std;

/**
 * LEDテープ
 */
class LedStrip {
   public:
    LedStrip(int index, int length);
    ~LedStrip();

    /**
     * テープLEDのindexを取得
     */
    int getIndex();

    /**
     * LEDの数を取得
     */
    int getLength();

    /**
     * 全体的な明るさを変更
     */
    void setPowerScale(float powerScale);

    /**
     * LEDドットに色をセット
     */
    void setPixels(vector<LedPixel *> *pixels);

    /**
     * LEDドットに色をセット
     */
    void setPixel(int color);

    /**
     * LEDドットに色をセット
     */
    void setPixel(int position, int color);

    /**
     * LEDドットに色をセット
     */
    void setPixel(int position, LedPixel *pixel);

    /**
     * シリアライズする
     */
    void serialize(vector<uint8_t> &packet);

   private:
    /**
     * LED
     */
    vector<LedPixel *> pixels;

    /**
     * テープLEDのindex
     */
    int index;

    /**
     * LEDの数
     */
    int length;

    /**
     * 全体的な明るさを変更するためのオプション(初期値:1.0f)
     */
    float powerScale;

    /**
     * 色が変更されたフラグ
     */
    bool touched;
};