#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

  for (int i = 0; i < 7; i++) {
    makerList.push_back(new CalibrationPointMaker());
  }

  for (int i = 0; i < makerList.size(); i++) {
    makerList[i]->setup(i);
  }
}

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(255 * .15);
  for (int i = 0; i < makerList.size(); i++) {
    makerList[i]->draw();
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
  if (key == OF_KEY_RETURN) {
    for (int i = 0; i < makerList.size(); i++) {
      makerList[i]->save();
    }
  }
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

//#include "ofApp.h"
//
////--------------------------------------------------------------
// void ofApp::setup() {
//
//
//
//  isSaved = false;
//
//  textField["total"] = new ofxTextInputField();
//  textField["diff"] = new ofxTextInputField();
//  textField["startId"] = new ofxTextInputField();
//  textField["posX"] = new ofxTextInputField();
//  textField["posY"] = new ofxTextInputField();
//  textField["startPosZ"] = new ofxTextInputField();
//  textField["fileName"] = new ofxTextInputField();
//
//  int i = 0;
//  for (auto itr = textField.begin(); itr != textField.end(); ++itr) {
//    itr->second->setup();
//    itr->second->bounds.height = 20;
//    itr->second->bounds.y = 50;
//
//    if (itr->first == "fileName") {
//      itr->second->bounds.width = 140;
//      itr->second->bounds.x =
//          ofGetWindowWidth() - itr->second->bounds.width - 10;
//    } else {
//      itr->second->bounds.width = 80;
//      itr->second->bounds.x = 10 + itr->second->bounds.width * i;
//    }
//    i++;
//  }
//  textField["diff"]->text = "120";
//  textField["total"]->text = "25";
//  textField["fileName"]->text = ".xml";
//}
//
////--------------------------------------------------------------
// void ofApp::update() {}
//
////--------------------------------------------------------------
// void ofApp::draw() {
//  ofBackground(255 * .15);
//  ofSetColor(255);
//
//
//
//
//  for (auto itr = textField.begin(); itr != textField.end(); ++itr) {
//    ofRect(itr->second->bounds);
//    ofDrawBitmapString(itr->first, ofPoint(itr->second->bounds.x + 5,
//                                           itr->second->bounds.y - 5));
//  }
//  ofNoFill();
//  for (auto itr = textField.begin(); itr != textField.end(); ++itr) {
//    itr->second->draw();
//  }
//
//  if (isSaved) {
//    ofSetColor(255, 0, 0);
//    ofDrawBitmapString("saved!", ofPoint(10, ofGetWindowHeight() - 10));
//  } else {
//    ofSetColor(255);
//    ofDrawBitmapString("no save", ofPoint(10, ofGetWindowHeight() - 10));
//  }
//}
//
////--------------------------------------------------------------
// void ofApp::save() {
//  int total = ofToInt(textField["total"]->text);
//  int diff = ofToInt(textField["diff"]->text);
//  int startId = ofToInt(textField["startId"]->text);
//  int posX = ofToInt(textField["posX"]->text);
//  int posY = ofToInt(textField["posY"]->text);
//  int startPosZ = ofToInt(textField["startPosZ"]->text);
//
//  ofLogNotice() << total;
//  ofLogNotice() << diff;
//  ofLogNotice() << startId;
//  ofLogNotice() << posX;
//  ofLogNotice() << posY;
//  ofLogNotice() << startPosZ;
//
//  ofxXmlSettings xml;
//  for (int i = 0; i < total; i++) {
//    xml.addTag("calibration_point");
//    xml.pushTag("calibration_point", i);
//    xml.setValue("id", startId);
//    xml.addTag("position");
//    xml.pushTag("position");
//    xml.setValue("x", posX);
//    xml.setValue("y", posY);
//    xml.setValue("z", startPosZ);
//    xml.popTag();
//    xml.popTag();
//    startId++;
//    startPosZ += diff;
//  }
//  xml.save(textField["fileName"]->text);
//  isSaved = true;
//}
//
////--------------------------------------------------------------
// void ofApp::keyPressed(int key) {}
//
////--------------------------------------------------------------
// void ofApp::keyReleased(int key) {
//  if (key == OF_KEY_RETURN) {
//    save();
//  }
//}
//
////--------------------------------------------------------------
// void ofApp::mouseMoved(int x, int y) {}
//
////--------------------------------------------------------------
// void ofApp::mouseDragged(int x, int y, int button) {}
//
////--------------------------------------------------------------
// void ofApp::mousePressed(int x, int y, int button) {}
//
////--------------------------------------------------------------
// void ofApp::mouseReleased(int x, int y, int button) {}
//
////--------------------------------------------------------------
// void ofApp::mouseEntered(int x, int y) {}
//
////--------------------------------------------------------------
// void ofApp::mouseExited(int x, int y) {}
//
////--------------------------------------------------------------
// void ofApp::windowResized(int w, int h) {}
//
////--------------------------------------------------------------
// void ofApp::gotMessage(ofMessage msg) {}
//
////--------------------------------------------------------------
// void ofApp::dragEvent(ofDragInfo dragInfo) {}
