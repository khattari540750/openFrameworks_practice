#include "ofApp.h"

void receive_sensorA(SensorA *data, double *time) {
  static double a, b;
  static int c;
  a += 0.1;
  b += 0.01;
  c++;
  data->a = a;
  data->b = b;
  data->c = c;
  *time = gettimeSSM();
  usleep(100000);
}

//--------------------------------------------------------------
void ofApp::setup() {
  initSSM();
  sensA_sid = createSSM("sensor_A", 0, sizeof(SensorA), 10, 0.1);

  sens_prop.a = 100;
  sprintf(sens_prop.name, "sensorA");
  set_propertySSM("sensor_A", 0, (char *)&sens_prop, sizeof(SensorA_Property));

  ofSetFrameRate(10);
}

//--------------------------------------------------------------
void ofApp::update() {
  receive_sensorA(&sens_data, &measured_time);
  printf("%d\n", writeSSM(sensA_sid, (char *)&sens_data, measured_time));
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
