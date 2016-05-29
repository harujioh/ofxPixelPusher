#pragma once

#include "ofMain.h"

#include "ofxPixelPusher.h"

class ofApp : public ofBaseApp {
   public:
    void setup();
    void update();
    void draw();

   private:
    ofxPixelPusher pixelPusher;

    uint8_t phase = 0;

    void fade(ofColor color, int delay = 10);
};
