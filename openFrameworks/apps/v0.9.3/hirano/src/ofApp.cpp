#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  img.load("img.jpg");
  img.resize(ofGetWidth(), ofGetHeight());

  sound.load("sakebi.mp3");
  sound.play();
  startSound = ofGetSeconds();

  sound2.load("happy.mp3");
  flag = true;

  font.load("Sudbury_Basin_3D.ttf", 50);
}

//--------------------------------------------------------------
void ofApp::update() {
  if (ofGetSeconds() - startSound > 2 && flag) {
    sound.stop();
    sound2.play();
    flag = false;
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofSetHexColor(0xFFFFFF);
  img.draw(0, 0);

  if (!flag) {
    string tempStr = "Happy BirthDay!";
    float widthDiv = ofGetWidth() / 3.8f;
    ofSetHexColor(0xFF0000);
    font.drawString(tempStr, widthDiv, ofGetHeight() - 50);
  }
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
