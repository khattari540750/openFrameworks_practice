#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  ofBackground(0);

  urg.setMode(ofxUrg::DISTANCE_INTENSITY);
  urg.setupEthernet();

  ofLogNotice("Product", urg.productType());
  ofLogNotice("Serial", urg.serialId());
  ofLogNotice("Status", urg.status());
  ofLogNotice("State", urg.state());
  ofLogNotice("Firmware version", urg.firmwareVersion());

  urg.start();
}

//--------------------------------------------------------------
void ofApp::update() { urg.update(); }

//--------------------------------------------------------------
void ofApp::draw() {
  cam.begin();
  ofPushMatrix();
  float s = 0.1;
  ofScale(s, s, s);
  ofRotateZ(-90);
  urg.drawDebugPolar();
  ofPopMatrix();
  cam.end();

  ofDrawBitmapString(ofToString(ofGetFrameRate(), 0), 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
