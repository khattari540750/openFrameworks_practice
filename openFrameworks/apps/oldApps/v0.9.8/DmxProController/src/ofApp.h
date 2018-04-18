#pragma once

#include "DataReaderConfig.hpp"
#include "ofMain.h"
#include "ofxDmx.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
  void setup();
  void exit();
  void update();
  void draw();

public:
  DataReaderConfig dataReaderConfig;
  ofxDmx dmx;
  ofxPanel panel;
  vector<ofParameter<int>> chanList;
};
