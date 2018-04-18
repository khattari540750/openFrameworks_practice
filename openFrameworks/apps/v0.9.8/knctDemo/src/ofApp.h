#pragma once
#include "Bug.h"
#include "Bullet.h"
#include "GameEvent.h"
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxOsc.h"

#include "ofxOpenCv.h"

#define _USE_LIVE_VIDEO // uncomment this to use a live camera
// otherwise, we'll use a movie file

class ofApp : public ofBaseApp {

public:
  void setup();
  void update();
  void draw();
  void exit();

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

  static bool shouldRemoveBullet(Bullet &b);
  static bool shouldRemoveBug(Bug &b);

private:
  void gameEvent(GameEvent &e);
  void bang();
  void hitColor();
  void sendColor(int r, int g, int b, int fadetime);
  void gameDraw();
  void cameraDraw();

private:
  bool isCamMode = true;

  ofxOscReceiver receiver;
  ofxOscSender sender;

  vector<Bullet> bullets;
  vector<Bug> bugs;
  vector<ofVec2f> holes;

  unsigned int maxBullets;
  int bugsKilled;
  bool bFire;

  ofColor bulletColor;

  int myW;
  int myH;

// camera
#ifdef _USE_LIVE_VIDEO
  ofVideoGrabber vidGrabber;
#else
  ofVideoPlayer vidPlayer;
#endif

  ofxCvColorImage colorImg;

  ofxCvGrayscaleImage grayImage;
  ofxCvGrayscaleImage grayBg;
  ofxCvGrayscaleImage grayDiff;

  ofxCvContourFinder contourFinder;

  int threshold;
  bool bLearnBakground;
};

//#pragma once
//
//#include "ofMain.h"
//
//#include "ofxOpenCv.h"
//
//#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
//// otherwise, we'll use a movie file
//
// class ofApp : public ofBaseApp{
//
// public:
//    void setup();
//    void update();
//    void draw();
//
//    void keyPressed(int key);
//    void keyReleased(int key);
//    void mouseMoved(int x, int y );
//    void mouseDragged(int x, int y, int button);
//    void mousePressed(int x, int y, int button);
//    void mouseReleased(int x, int y, int button);
//    void mouseEntered(int x, int y);
//    void mouseExited(int x, int y);
//    void windowResized(int w, int h);
//    void dragEvent(ofDragInfo dragInfo);
//    void gotMessage(ofMessage msg);
//
//#ifdef _USE_LIVE_VIDEO
//		  ofVideoGrabber 		vidGrabber;
//#else
//		  ofVideoPlayer 		vidPlayer;
//#endif
//
//    ofxCvColorImage			colorImg;
//
//    ofxCvGrayscaleImage 	grayImage;
//    ofxCvGrayscaleImage 	grayBg;
//    ofxCvGrayscaleImage 	grayDiff;
//
//    ofxCvContourFinder 	contourFinder;
//
//    int 				threshold;
//    bool				bLearnBakground;
//
//
//};
//