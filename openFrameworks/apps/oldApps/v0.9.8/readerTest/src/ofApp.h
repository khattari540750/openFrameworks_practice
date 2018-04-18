#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp {

public:
  void setup();
  void update();
  void draw();
};

class DataReader {
public:
  string test;
  void loadXml(string path);
};
