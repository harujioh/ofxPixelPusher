#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(10);
    ofSetLogLevel(ofLogLevel::OF_LOG_VERBOSE);

    pixelPusher.start();
}

//--------------------------------------------------------------
void ofApp::update() {
    switch (phase) {
        case 0:
            fade(ofColor::red);
            break;
        case 1:
            fade(ofColor::green);
            break;
        case 2:
            fade(ofColor::blue);
            break;
        case 3:
            fade(ofColor::white);
            break;
    }
    phase = (phase + 1) % 4;
}

//--------------------------------------------------------------
void ofApp::draw() {}

void ofApp::fade(ofColor color, int delay) {
    for (float rate = 0; rate < 1; rate += 0.01) {
        pixelPusher.setColor(color, rate);
        ofSleepMillis(delay);
    }
    pixelPusher.setColor(color, 1);
    for (float rate = 1; rate > 0; rate -= 0.01) {
        pixelPusher.setColor(color, rate);
        ofSleepMillis(delay);
    }
    pixelPusher.setColor(color, 0);
}