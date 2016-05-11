#pragma once

#include "ofMain.h"

#include "ofxPixelPusher.h"

class ofApp : public ofBaseApp {
   public:
    void setup();
    void update();
    void draw();

    void keyReleased(int key);

   private:
    ofxPixelPusher pixelPusher;
};
