#include "ofApp.h"

////--------------------------------------------------------------
// void ofApp::listenerTimerCount(string &name) {
//  //  ofLogNotice("example::listenerTimerCount")
//  //      << "name : " << name << ", count : " << timer.getLoopCurrentCount()
//  //      << " / " << timer.getLoopTotalCount();
//}
//
////--------------------------------------------------------------
// void ofApp::listenerTimerCompelte(string &name) {
//  //  ofLogNotice("example::listenerTimerCompelte") << name;
//}

//--------------------------------------------------------------
void ofApp::setup() {

  ofSetWindowShape(400, 400);
  dmx.connect("tty.usbserial-EN187538"); // use the name
  ofSetVerticalSync(true);
  panel.setup();
  panel.setName("tty.usbserial-EN187538");

  int channelTotal = 5;

  // add sliders to panel
  for (int i = 0; i < channelTotal; i++) {
    ofParameter<int> chan;
    string str = "channel " + ofToString(i + 1);
    chan.set(str, 0, 0, 255);
    panel.add(chan);
  }

  //  ofSetWindowShape(200, 200);
  //
  //  timer.setup(timer_name, duration, repeat_count);
  //  timer.start();
  //
  //  ofAddListener(ofxSimpleTimer::TIMER_COUNT, this,
  //  &ofApp::listenerTimerCount);
  //  ofAddListener(ofxSimpleTimer::TIMER_COMPLETE, this,
  //                &ofApp::listenerTimerCompelte);
}

//--------------------------------------------------------------
void ofApp::exit() {
  dmx.clear();
  dmx.update(true); // black on shutdown
}

//--------------------------------------------------------------
void ofApp::update() {
    
    // dmx
    for (int i = 0; i < chanList.size(); i++) {
        dmx.setLevel(1 + i, chanList[i]);
    }
    dmx.update();
    
    
  //  if (timer.isStarting())
  //    timer.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    panel.draw();
    
  //  float w = ofMap(timer.getCurrentTime(), 0, duration, 0.0, 1.0);
  //  ofSetColor(255, 0, 0);
  //  ofDrawRectangle(0, 0, w * ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
  //  switch (key) {
  //  case 's':
  //    timer.start(); // start
  //    break;
  //  case 'r':
  //    timer.reset(); // reset
  //    timer.start(); // start
  //    break;
  //  case 'p':
  //    timer.pause(); // pause
  //    break;
  //  default:
  //    break;
  //  }
}

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
