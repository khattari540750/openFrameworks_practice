#pragma once

#include "ofMain.h"
#include "ofxSsm.h"

typedef struct {
  double a;
  double b;
  int c;
} SensorA;

typedef struct {
  double a;
  char name[10];
} SensorA_Property;

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

  double measured_time;
  SSM_sid sensA_sid;
  SensorA_Property sens_prop;
  SensorA sens_data;
};
