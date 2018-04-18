#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

  dmx = new ofxDmx();
  dmx->connect("/dev/tty.usbserial-EN134034", 512);

  ofSetVerticalSync(true);

  gui.setup(); // most of the time you don't need a name
  for (int i = 0; i < 16; i++) {
      
      
      gui.add();
  }

  gui.add(circleResolution.setup("0", 0, 0, 255));
}

//--------------------------------------------------------------
void ofApp::exit() {}

//--------------------------------------------------------------
void ofApp::update() {

  if (dmx->isConnected()) {
    for (int i = 0; i < 16; i++) {
      dmx->setLevel(200 + i, 0);
    }
    dmx->update();
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofBackgroundGradient(ofColor::white, ofColor::gray);

  // auto draw?
  // should the gui control hiding?
  gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    gui.saveToFile("settings.xml");
  } else if (key == 'l') {
    gui.loadFromFile("settings.xml");
  } else if (key == ' ') {
    color = ofColor(255);
  }
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
void ofApp::windowResized(int w, int h) {
  screenSize = ofToString(w) + "x" + ofToString(h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
