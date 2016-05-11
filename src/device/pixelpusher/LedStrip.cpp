#include "LedStrip.h"

LedStrip::LedStrip(int stripNumber, int length) : index(stripNumber), length(length) {
    for (int i = 0; i < length; i++) {
        pixels.push_back(new LedPixel);
    }
    powerScale = 1.0f;
    touched = false;
}

LedStrip::~LedStrip() {
    for (LedPixel *pixel : pixels) {
        delete pixel;
    }
}

int LedStrip::getIndex() { return index; }

int LedStrip::getLength() { return length; }

void LedStrip::setPowerScale(float powerScale) { this->powerScale = powerScale; }

void LedStrip::setPixels(vector<LedPixel *> *pixels) {
    if (pixels->size() > 0 && length > 0) {
        touched = true;
    }

    for (int i = 0; i < pixels->size() && i < length; i++) {
        this->pixels[i]->setColor(*(*pixels)[i]);
    }

    if (pixels->size() > length) {
        for (int i = length; i < pixels->size(); i++) {
            this->pixels.push_back(new LedPixel(*(*pixels)[i]));
        }
    }
}

void LedStrip::setPixel(int color) {
    for (int i = 0; i < pixels.size(); i++) {
        pixels[i]->setColor(color);
    }
    touched = true;
}

void LedStrip::setPixel(int position, int color) {
    if (position < length) {
        pixels[position]->setColor(color);
        touched = true;
    }
}

void LedStrip::setPixel(int position, LedPixel *pixel) {
    if (position < length) {
        pixels[position]->setColor(*pixel);
        touched = true;
    }
}

void LedStrip::serialize(vector<uint8_t> &packet) {
    if (!touched) {
        return;
    }

    touched = false;
    packet.push_back(index);
    for (int i = 0; i < pixels.size(); i++) {
        packet.push_back((uint8_t)(pixels[i]->red * powerScale));
        packet.push_back((uint8_t)(pixels[i]->green * powerScale));
        packet.push_back((uint8_t)(pixels[i]->blue * powerScale));
    }
}