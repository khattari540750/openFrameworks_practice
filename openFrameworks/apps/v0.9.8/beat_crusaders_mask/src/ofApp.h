#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"

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

public:
  ofVideoGrabber vidGrabber;
  ofxCvColorImage cameraImage;
  ofxCvGrayscaleImage grayImage;

  ofxCvColorImage mosaicImage;
  ofxCvGrayscaleImage monoImage;
  ofImage cutImage;

  // pixels;
  int imageWidth = 32;
  int imageHeight = 16;

  ofxPanel gui;
  ofxIntSlider resolution;
  ofxIntSlider threshold;

  ofSerial serial;
  vector<ofColor> colorList;
};