#pragma once

#include <stdint.h>

/**
 * LEDテープの1ドット
 */
class LedPixel {
   public:
    LedPixel();
    LedPixel(const LedPixel& pixel);
    LedPixel(uint8_t red, uint8_t green, uint8_t blue);

    /**
     * 色を設定
     */
    void setColor(int color);

    /**
     * 色を設定
     */
    void setColor(LedPixel pixel);

    /**
     * red
     */
    uint8_t red;

    /**
     * red
     */
    uint8_t green;

    /**
     * red
     */
    uint8_t blue;
};