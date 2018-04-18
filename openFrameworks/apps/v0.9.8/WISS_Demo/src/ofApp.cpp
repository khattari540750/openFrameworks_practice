#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

  ofBackground(255, 255, 255);

  // シリアル通信開始
  serial.setup("/dev/tty.usbmodem1411", 9600);

  // osc
  sender.setup("192.168.1.2", 8888);
  // sender.setup("172.16.2.18", 8888);
}

//--------------------------------------------------------------
void ofApp::update() {
  nBytesRead = 0;
  int nRead = 0;
  char bytesRead[4];
  unsigned char bytesReturned[4];

  memset(bytesReturned, 0, 4);
  memset(bytesReadString, 0, 5);

  // シリアル通信で受け取ったデータを読み込む
  while ((nRead = serial.readBytes(bytesReturned, 4)) > 0) {
    nBytesRead = nRead;
  };

  if (nBytesRead > 0) {
    ofLogNotice("") << "data Read!:" << nBytesRead << endl;
    memcpy(bytesReadString, bytesReturned, 4);

    if (nBytesRead == 1) {
      string recv = ofToString(bytesReadString);
      if (recv == "B") {
        ofxOscMessage m;
        m.setAddress("/interaction");
        m.addIntArg(0);
        sender.sendMessage(m);
        ofLogNotice("") << "send osc 0" << endl;
      }
      if (recv == "T") {
        ofxOscMessage m;
        m.setAddress("/interaction");
        m.addIntArg(1);
        sender.sendMessage(m);
        ofLogNotice("") << "send osc 1" << endl;
      } else {
        float k = (float)ofToInt(bytesReadString);
        float val = ofMap(k, 0, 1023, 0., 1.);
        ofxOscMessage m;
        m.setAddress("/interaction");
        m.addIntArg(2);
        m.addFloatArg(0);
        sender.sendMessage(m);
        ofLogNotice("") << "send osc 2" << endl;
      }
    } else {
      ofxOscMessage m;
      m.setAddress("/interaction");
      m.addIntArg(2);
      m.addFloatArg(1);
      sender.sendMessage(m);
      ofLogNotice("") << "send osc 2" << endl;
      // ofLogNotice("") << "send osc 2 " << bytesReadString << endl;
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  // 送られてきた文字列を表示
  string msg;
  msg += ofToString(nBytesRead) + " [bytes]" + "\n";
  msg += "read: " + ofToString(bytesReadString);
  ofSetColor(0);
  ofDrawBitmapString(msg, 100, 100);
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
