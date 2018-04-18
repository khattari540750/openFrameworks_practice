//!
//! @file ofApp.h
//! @brief 3D icp test
//! @author HATTORI Kohei
//! @date 4/7/2016
//!

#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "icp.hpp"

class ofApp : public ofBaseApp {

public:
  void setup();
  void update();
  void draw();

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

private:
  double toRadian(double degree);
  cv::Mat ofMat2cvMat(ofMatrix4x4 ofMat);

private:
  ICP icp;
  cv::Mat drawBaseData;
  cv::Mat drawMeasurementData;
  cv::Mat drawFixData;
  bool fixFlag;
  ofEasyCam cam;
  vector<ofSpherePrimitive> baseDataObjsList;
  vector<ofSpherePrimitive> measurementDataObjsList;
  vector<ofSpherePrimitive> modifiedDataObjsList;
};
