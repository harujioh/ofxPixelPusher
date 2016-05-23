#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(10);
    ofSetLogLevel(ofLogLevel::OF_LOG_VERBOSE);

    pixelPusher.start();
}

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {}

void ofApp::keyReleased(int key) {
    switch (key) {
        case '1':
            pixelPusher.setColor(ofColor::red);
            break;
        case '2':
            pixelPusher.setColor(ofColor::green);
            break;
        case '3':
            pixelPusher.setColor(ofColor::blue);
            break;
        case '4':
            pixelPusher.setColor(ofColor::white);
            break;
        case '5':
            pixelPusher.setColor(ofColor::black);
            break;
        case '6':
            for (int i = 0; i < 256; i++) {
                pixelPusher.setColor(2, 1, 0, i, ofColor::red);
                ofSleepMillis(1);
            }
            break;
        case '7':
            for (int i = 0; i < 256; i++) {
                pixelPusher.setColor(2, 1, 0, i, ofColor::green);
                ofSleepMillis(1);
            }
            break;
        case '8':
            for (int i = 0; i < 256; i++) {
                pixelPusher.setColor(2, 1, 0, i, ofColor::blue);
                ofSleepMillis(1);
            }
            break;
    }
}