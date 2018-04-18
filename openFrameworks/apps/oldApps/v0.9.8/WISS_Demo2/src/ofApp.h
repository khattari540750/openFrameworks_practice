#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

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

  void setupArduino(const int &version);
  void updateArduino();

  bool bSetupArduino;
  int inputPin = 2;
  int ledPin = 7;
  int buttonPin = 3;
  int touchPin = 4;
  int anglePin = 14;

  ofArduino ard;
  ofxOscSender sender;
};
