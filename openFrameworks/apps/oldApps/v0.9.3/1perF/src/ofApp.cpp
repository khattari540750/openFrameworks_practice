#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  cnt = 50;
  for (int i = 0; i < cnt; i++) {
    signals.push_back(0);
  }
}

//--------------------------------------------------------------
void ofApp::update() {
  for (int i = 1; i <= (cnt - 1); i++) {
    signals[i - 1] = signals[i];
  }
  signals[cnt - 1] = function.calc();

  for (int i = 0; i < cnt; i++) {
    output += signals[i];
  }
  output = output / (float)cnt;
  output += 0.3;
  cout << output << endl;
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofSetColor(ofColor(ofMap(output, 0, 1, 0, 255), 0, 0));
  ofDrawCircle(ofVec2f(100, 100), 50);
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
