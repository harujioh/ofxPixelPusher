#include "LedPixel.h"

LedPixel::LedPixel() {
    red = 0;
    blue = 0;
    green = 0;
}

LedPixel::LedPixel(const LedPixel& pixel) {
    red = pixel.red;
    blue = pixel.blue;
    green = pixel.green;
}

LedPixel::LedPixel(uint8_t red, uint8_t green, uint8_t blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}

void LedPixel::setColor(int color) {
    blue = color & 0xff;
    green = (color >> 8) & 0xff;
    red = (color >> 16) & 0xff;
}

void LedPixel::setColor(LedPixel pixel) {
    red = pixel.red;
    blue = pixel.blue;
    green = pixel.green;
}