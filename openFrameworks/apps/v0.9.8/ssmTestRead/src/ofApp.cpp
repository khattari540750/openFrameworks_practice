#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  initSSM();
  sensA_sid = openSSM("sensor_A", 0, 0);
}

//--------------------------------------------------------------
void ofApp::update() {
  now_time = gettimeSSM();

  tid =
      readSSM_time(sensA_sid, (char *)&sens_data, now_time - 1, &measured_time);
  printf("nowtime=%f\n   time=%f tid=%d a=%f b=%f c=%d\n", gettimeSSM() - 1,
         measured_time, tid, sens_data.a, sens_data.b, sens_data.c);

  tid = readSSM(sensA_sid, (char *)&sens_data, &measured_time, tid + 1);
  printf("   time=%f tid=%d a=%f b=%f c=%d\n\n", measured_time, tid,
         sens_data.a, sens_data.b, sens_data.c);
}

//--------------------------------------------------------------
void ofApp::draw() {}

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
