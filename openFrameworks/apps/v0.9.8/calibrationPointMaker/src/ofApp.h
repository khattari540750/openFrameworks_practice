#pragma once

#include "CalibrationPointMaker.h"
#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
  void setup();
  void update();
  void draw();

  void save();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

  vector<CalibrationPointMaker *> makerList;
};

//#pragma once
//
//#include "ofMain.h"
//#include "ofxTextInputField.h"
//#include "ofxXmlSettings.h"
//
// class CalibrationPoint {
//  int id;
//  ofVec3f position;
//};
//
// class ofApp : public ofBaseApp {
//
// public:
//  void setup();
//  void update();
//  void draw();
//
//  void save();
//
//  void keyPressed(int key);
//  void keyReleased(int key);
//  void mouseMoved(int x, int y);
//  void mouseDragged(int x, int y, int button);
//  void mousePressed(int x, int y, int button);
//  void mouseReleased(int x, int y, int button);
//  void mouseEntered(int x, int y);
//  void mouseExited(int x, int y);
//  void windowResized(int w, int h);
//  void dragEvent(ofDragInfo dragInfo);
//  void gotMessage(ofMessage msg);
//
//  map<string, ofxTextInputField *> textField;
//  bool isSaved;
//};
