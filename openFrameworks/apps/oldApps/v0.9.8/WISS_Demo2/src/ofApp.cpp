#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetFrameRate(60); //フレームレート60fpsで描画
  ofBackground(0);    //背景を黒に設定

  ard.connect("/dev/tty.usbmodem1411", 57600);
  ofAddListener(ard.EInitialized, this,
                &ofApp::setupArduino); //イベントリスナーを登録
  bSetupArduino = false;               //通信状態はfalseに設定
}

//--------------------------------------------------------------
void ofApp::update() { updateArduino(); }

//--------------------------------------------------------------
void ofApp::draw() {
  // arduinoと通信していたら
  if (bSetupArduino) {
    //指定したデジタルピンにインプットがあったら
    if (ard.getDigital(buttonPin) == 1) {
      ofLogNotice("") << "button" << endl;
    }

    if (ard.getDigital(touchPin) == 1) {
      ofLogNotice("") << "touch" << endl;
    }
  }
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int &version) {
  ofRemoveListener(ard.EInitialized, this,
                   &ofApp::setupArduino); //イベントリスナーを削除
  ard.sendDigitalPinMode(ledPin, ARD_OUTPUT);
  ard.sendDigitalPinMode(buttonPin, ARD_INPUT);
  ard.sendDigitalPinMode(touchPin, ARD_INPUT);
  
  ard.getAnalog(<#int pin#>, ARD_ANALOG);
  bSetupArduino = true;
}

//--------------------------------------------------------------
void ofApp::updateArduino() { ard.update(); }

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
