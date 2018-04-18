//!
//! @file CalibrationPointMaker.cpp
//! @brief CalibrationPointMaker source file
//!

#include "CalibrationPointMaker.h"

//--------------------------------------------------------------
void CalibrationPointMaker::setup(int num) {
  isSaved = false;
  textField["total"] = new ofxTextInputField();
  textField["diff"] = new ofxTextInputField();
  textField["startId"] = new ofxTextInputField();
  textField["posX"] = new ofxTextInputField();
  textField["posY"] = new ofxTextInputField();
  textField["startPosZ"] = new ofxTextInputField();
  textField["fileName"] = new ofxTextInputField();

  int i = 0;
  for (auto itr = textField.begin(); itr != textField.end(); ++itr) {
    itr->second->setup();
    itr->second->bounds.height = 20;
    itr->second->bounds.y = (10 + itr->second->bounds.height * 2) * (num+1);

    if (itr->first == "fileName") {
      itr->second->bounds.width = 140;
      itr->second->bounds.x =
          ofGetWindowWidth() - itr->second->bounds.width - 10;
    } else {
      itr->second->bounds.width = 80;
      itr->second->bounds.x = 10 + itr->second->bounds.width * i;
    }
    i++;
  }
  textField["diff"]->text = "-900";
  textField["total"]->text = "3";
  textField["startPosZ"]->text = "5400";
  textField["fileName"]->text = "calibrationPoint001.xml";
}

//--------------------------------------------------------------
void CalibrationPointMaker::draw() {

  ofSetColor(255);
  for (auto itr = textField.begin(); itr != textField.end(); ++itr) {
    ofDrawRectangle(itr->second->bounds);
    ofDrawBitmapString(itr->first, ofPoint(itr->second->bounds.x + 5,
                                           itr->second->bounds.y - 5));
  }
  ofNoFill();
  for (auto itr = textField.begin(); itr != textField.end(); ++itr) {
    itr->second->draw();
  }

  if (isSaved) {
    ofSetColor(255, 0, 0);
    ofDrawBitmapString("saved!", ofPoint(10, ofGetWindowHeight() - 10));
  } else {
    ofSetColor(255);
    ofDrawBitmapString("no save", ofPoint(10, ofGetWindowHeight() - 10));
  }
}

//--------------------------------------------------------------
void CalibrationPointMaker::save() {
  int total = ofToInt(textField["total"]->text);
  int diff = ofToInt(textField["diff"]->text);
  int startId = ofToInt(textField["startId"]->text);
  int posX = ofToInt(textField["posX"]->text);
  int posY = ofToInt(textField["posY"]->text);
  int startPosZ = ofToInt(textField["startPosZ"]->text);

  ofLogNotice() << total;
  ofLogNotice() << diff;
  ofLogNotice() << startId;
  ofLogNotice() << posX;
  ofLogNotice() << posY;
  ofLogNotice() << startPosZ;

  ofxXmlSettings xml;
  for (int i = 0; i < total; i++) {
    xml.addTag("calibration_point");
    xml.pushTag("calibration_point", i);
    xml.setValue("id", startId);
    xml.addTag("position");
    xml.pushTag("position");
    xml.setValue("x", posX);
    xml.setValue("y", posY);
    xml.setValue("z", startPosZ);
    xml.popTag();
    xml.popTag();
    startId++;
    startPosZ += diff;
  }
  xml.save(textField["fileName"]->text);
  isSaved = true;
}