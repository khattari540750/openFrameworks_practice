#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofBackground(40, 100, 40);
  ofSetFrameRate(60);

  // open an outgoing connection to HOST:PORT
  sender.setup(HOST, PORT);

  cnt = 500;
  cntPlus = true;
}

//--------------------------------------------------------------
void ofApp::update() {
  // out put
  ofxOscMessage devA;
  devA.setAddress("/deviceA");
  for (int i = 0; i < 24; i++)
    devA.addIntArg(cnt);
  sender.sendMessage(devA, false);

  ofxOscMessage devB;
  devB.setAddress("/deviceB");
  for (int i = 0; i < 24; i++)
    devB.addIntArg(cnt);
  sender.sendMessage(devB, false);

  if (cntPlus)
    cnt += 30;
  else
    cnt -= 30;
  if (cnt >= 2400)
    cntPlus = false;
  if (cnt <= 500)
    cntPlus = true;
}

//--------------------------------------------------------------
void ofApp::draw() {
  // display instructions
  string buf;
  buf = "sending osc messages to " + string(HOST) + ofToString(PORT);
  ofDrawBitmapString(buf, 10, 20);
  buf = "press A to send osc message " + ofToString(cnt);
  ofDrawBitmapString(buf, 10, 80);
  ofDrawBitmapString("FPS : " + ofToString(ofGetFrameRate()),
                     ofPoint(10, ofGetWindowHeight() - 10));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  //  if (key == 'a' || key == 'A') {
  //    ofxOscMessage m;
  //    m.setAddress("/deviceA");
  //    for (int i = 0; i < 24; i++) m.addIntArg(2400);
  //    sender.sendMessage(m, false);
  //  }
  //
  //  if (key == 's' || key == 'S') {
  //    ofxOscMessage m;
  //    m.setAddress("/deviceA");
  //    for (int i = 0; i < 24; i++) m.addIntArg(500);
  //    sender.sendMessage(m, false);
  //  }
  //
  //  if (key == 'd' || key == 'D') {
  //    ofxOscMessage m;
  //    m.setAddress("/deviceA");
  //    for (int i = 0; i < 24; i++) m.addIntArg(1450);
  //    sender.sendMessage(m, false);
  //  }
}

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