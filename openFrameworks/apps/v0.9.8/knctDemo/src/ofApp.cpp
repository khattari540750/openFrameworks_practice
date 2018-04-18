#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

  ofBackgroundHex(0xc5c9b2);
  ofSetFrameRate(60);

  bFire = false;
  bugsKilled = 0;
  maxBullets = 30;

  // add some random holes for the bugs to come out
  int nHoldes = 10;
  for (int i = 0; i < nHoldes; i++) {
    ofVec2f p(ofRandomWidth(), ofRandomHeight());
    holes.push_back(p);
  }

  // listen to any of the events for the game
  ofAddListener(GameEvent::events, this, &ofApp::gameEvent);

  // osc setup
  receiver.setup(10002);
  sender.setup("192.168.12.11", 10002);
  sendColor(0, 0, 0, 500);

// camera
#ifdef _USE_LIVE_VIDEO
  vidGrabber.setVerbose(true);
  vidGrabber.setup(320, 240);
#else
  vidPlayer.load("fingers.mov");
  vidPlayer.play();
  vidPlayer.setLoopState(OF_LOOP_NORMAL);
#endif

  colorImg.allocate(320, 240);
  grayImage.allocate(320, 240);
  grayBg.allocate(320, 240);
  grayDiff.allocate(320, 240);

  bLearnBakground = true;
  threshold = 80;
}

//--------------------------------------------------------------
void ofApp::update() {

  if ((int)ofRandom(0, 20) == 10) {

    int randomHole = ofRandom(holes.size());

    Bug newBug;
    newBug.pos = holes[randomHole];
    newBug.vel.set(ofRandom(-1, 1), ofRandom(-1, 1));
    bugs.push_back(newBug);
  }

  for (unsigned int i = 0; i < bugs.size(); i++) {

    bugs[i].update();

    // bug pos and size
    float size = bugs[i].size;
    ofVec2f pos = bugs[i].pos;

    // wrap the bugs around the screen
    if (pos.x > ofGetWidth() - size)
      bugs[i].pos.x = -size;
    if (pos.x < -size)
      bugs[i].pos.x = ofGetWidth() - size;
    if (pos.y > ofGetHeight() + size)
      bugs[i].pos.y = -size;
    if (pos.y < -size)
      bugs[i].pos.y = ofGetHeight() - size;
  }

  // check if we should remove any bugs
  ofRemove(bugs, shouldRemoveBug);

  // update the bullets
  for (unsigned int i = 0; i < bullets.size(); i++) {
    bullets[i].update();
  }

  // check if we want to remove the bullet
  ofRemove(bullets, shouldRemoveBullet);

  // did we hit a bug loop we are checking to see if a bullet
  // hits a bug. if so we are going to launch an event for the game
  for (unsigned int i = 0; i < bullets.size(); i++) {
    for (unsigned int j = 0; j < bugs.size(); j++) {

      ofVec2f a = bullets[i].pos;
      ofVec2f b = bugs[j].pos;
      float minSize = bugs[j].size;

      if (a.distance(b) < minSize) {

        static GameEvent newEvent;
        newEvent.message = "BUG HIT";
        newEvent.bug = &bugs[j];
        newEvent.bullet = &bullets[i];

        ofNotifyEvent(GameEvent::events, newEvent);
      }
    }
  }

  // osc receiver loop
  while (receiver.hasWaitingMessages()) {
    ofxOscMessage msg;
    receiver.getNextMessage(msg);
    if (msg.getAddress() == "/comm/ball/touch") {
      bang();
      bulletColor.r = msg.getArgAsInt(1);
      bulletColor.g = msg.getArgAsInt(2);
      bulletColor.b = msg.getArgAsInt(3);
      // ofLogNotice("") << red << ","<< green << "," << blue;
      bFire = false;
    }
  }

  bool bNewFrame = false;

#ifdef _USE_LIVE_VIDEO
  vidGrabber.update();
  bNewFrame = vidGrabber.isFrameNew();
#else
  vidPlayer.update();
  bNewFrame = vidPlayer.isFrameNew();
#endif

  if (bNewFrame) {

#ifdef _USE_LIVE_VIDEO
    colorImg.setFromPixels(vidGrabber.getPixels());
#else
    colorImg.setFromPixels(vidPlayer.getPixels());
#endif

    grayImage = colorImg;
    if (bLearnBakground == true) {
      grayBg = grayImage;
      bLearnBakground = false;
    }

    grayDiff.absDiff(grayBg, grayImage);
    grayDiff.threshold(threshold);

    contourFinder.findContours(grayDiff, 20, (340 * 240) / 3, 10, true);
  }

  for (int i = 0; i < contourFinder.nBlobs; i++) {
    if (contourFinder.blobs[i].hole) {
      myW = contourFinder.blobs[i].boundingRect.getCenter().x;
      myH = contourFinder.blobs[i].boundingRect.getCenter().y;
      ofMap(myW, 0, 320, 0, ofGetWindowWidth());
      ofMap(myH, 0, 240, 0, ofGetWindowHeight());
    }
  }
  ofLogNotice() << myW << " " << myH;
}

//--------------------------------------------------------------
void ofApp::draw() {
  if (!isCamMode)
    gameDraw();
  else
    cameraDraw();
}

//--------------------------------------------------------------
void ofApp::exit() {
  sendColor(0, 0, 0, 500);
  ofLogNotice("exit");
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  switch (key) {
  case ' ':
    bLearnBakground = true;
    break;
  case '+':
    threshold++;
    if (threshold > 255)
      threshold = 255;
    break;
  case '-':
    threshold--;
    if (threshold < 0)
      threshold = 0;
    break;
  case 'c':
    isCamMode = !isCamMode;
    break;
  }

  //  if (key == ' ') {
  //    bang();
  //  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

  // bFire = false;
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

//--------------------------------------------------------------
bool ofApp::shouldRemoveBullet(Bullet &b) {

  if (b.bRemove)
    return true;

  bool bRemove = false;

  // get the rectangle of the OF world
  ofRectangle rec = ofGetCurrentViewport();

  // check if the bullet is inside the world
  if (rec.inside(b.pos) == false) {
    bRemove = true;
  }

  return bRemove;
}

//--------------------------------------------------------------
bool ofApp::shouldRemoveBug(Bug &b) { return b.bRemove; }

//--------------------------------------------------------------
void ofApp::gameEvent(GameEvent &e) {

  cout << "Game Event: " + e.message << endl;
  e.bug->timeBugKilled = ofGetElapsedTimef();
  e.bug->bSquashed = true;

  e.bullet->bRemove = true;

  bugsKilled++;
}

//--------------------------------------------------------------
void ofApp::bang() {
  if (bullets.size() < maxBullets) {
    bFire = true;
    Bullet b;

    // the two points for the mouse and gun
    ofVec2f gunPt(ofGetWidth() / 2, ofGetHeight() - 20);
    // ofVec2f mousePt(ofGetMouseX(), ofGetMouseY());
    // ofVec2f mousePt(myW, myH);
    ofVec2f mousePt(myW, 30);

    // the vector between the two
    ofVec2f vec = mousePt - gunPt;

    // normalize = 0.0 - 1.0
    vec.normalize();

    // bullet position = the start pos of the gun
    // and the vec scaled by 100
    ofVec2f bulletPos = gunPt + (vec * 100);

    b.pos = bulletPos;
    b.vel = vec * ofRandom(9, 12); // randomly make it faster
    b.bRemove = false;

    // add the bullets to the array
    bullets.push_back(b);
  }
}

//--------------------------------------------------------------
void ofApp::sendColor(int r, int g, int b, int fadetime) {
  ofxOscMessage msg;
  msg.setAddress("/comm/ball/color");
  msg.addIntArg(r);
  msg.addIntArg(g);
  msg.addIntArg(b);
  msg.addIntArg(fadetime);
  sender.sendMessage(msg);
}

//--------------------------------------------------------------
void ofApp::gameDraw() {
  // draw the bug holes
  for (unsigned int i = 0; i < holes.size(); i++) {
    ofSetColor(100);
    ofDrawCircle(holes[i], 10);
    ofSetColor(40);
    ofDrawCircle(holes[i], 7);
  }

  for (unsigned int i = 0; i < bugs.size(); i++) {
    bugs[i].draw();
  }

  // draw the bullets
  for (unsigned int i = 0; i < bullets.size(); i++) {
    bullets[i].draw(bulletColor);
  }

  // game stats
  ofSetColor(10);
  ofDrawBitmapString("Bullets " + ofToString(bullets.size()) +
                         "\nBugs Killed: " + ofToString(bugsKilled),
                     20, 20);

  // gun
  ofVec2f gunPos(ofGetWidth() / 2, ofGetHeight() - 20);
  // ofVec2f mousePos(ofGetMouseX(), ofGetMouseY());
  // ofVec2f mousePos(myW, myH);
  ofVec2f mousePos(myW, 30);

  // get the vector from the mouse to gun
  ofVec2f vec = mousePos - gunPos;
  vec.normalize();
  vec *= 100;

  // get the angle of the vector for rotating the rect
  float angle = ofRadToDeg(atan2(vec.y, vec.x)) - 90;
  // float angle = ofRadToDeg(cos());

  ofPushMatrix();
  ofTranslate(gunPos.x, gunPos.y);
  ofRotateZ(angle);

  ofFill();
  ofSetColor(10);
  ofDrawRectangle(-10, 0, 20, 100);

  float bulletPct = ofMap(bullets.size(), 0, maxBullets, 0.0, 100.0);
  ofSetColor(100);
  ofDrawRectangle(-10, 0, 20, bulletPct);

  ofSetColor(100);
  ofDrawRectangle(-10, 90, 20, 10);

  if (bFire) {
    ofSetColor(220, 0, 0);
    ofDrawRectangle(-10, 97, 20, 3);
  }
  ofPopMatrix();

  ofSetColor(255);
  ofDrawCircle(gunPos.x, gunPos.y, 2);
}

//--------------------------------------------------------------
void ofApp::cameraDraw() {
  // draw the incoming, the grayscale, the bg and the thresholded difference
  ofSetHexColor(0xffffff);
  colorImg.draw(20, 20);
  grayImage.draw(360, 20);
  grayBg.draw(20, 280);
  grayDiff.draw(360, 280);

  // then draw the contours:

  ofFill();
  ofSetHexColor(0x333333);
  ofDrawRectangle(360, 540, 320, 240);
  ofSetHexColor(0xffffff);

  // we could draw the whole contour finder
  // contourFinder.draw(360,540);

  // or, instead we can draw each blob individually from the blobs vector,
  // this is how to get access to them:
  for (int i = 0; i < contourFinder.nBlobs; i++) {
    contourFinder.blobs[i].draw(360, 540);

    // draw over the centroid if the blob is a hole
    ofSetColor(255);
    if (contourFinder.blobs[i].hole) {
      ofDrawBitmapString(
          "hole", contourFinder.blobs[i].boundingRect.getCenter().x + 360,
          contourFinder.blobs[i].boundingRect.getCenter().y + 540);
    }
  }

  // finally, a report:
  ofSetHexColor(0xffffff);
  stringstream reportStr;
  reportStr << "bg subtraction and blob detection" << endl
            << "press ' ' to capture bg" << endl
            << "threshold " << threshold << " (press: +/-)" << endl
            << "num blobs found " << contourFinder.nBlobs
            << ", fps: " << ofGetFrameRate();
  ofDrawBitmapString(reportStr.str(), 20, 600);
}

//#include "ofApp.h"
//
////--------------------------------------------------------------
// void ofApp::setup() {
//
//#ifdef _USE_LIVE_VIDEO
//  vidGrabber.setVerbose(true);
//  vidGrabber.setup(320, 240);
//#else
//  vidPlayer.load("fingers.mov");
//  vidPlayer.play();
//  vidPlayer.setLoopState(OF_LOOP_NORMAL);
//#endif
//
//  colorImg.allocate(320, 240);
//  grayImage.allocate(320, 240);
//  grayBg.allocate(320, 240);
//  grayDiff.allocate(320, 240);
//
//  bLearnBakground = true;
//  threshold = 80;
//}
//
////--------------------------------------------------------------
// void ofApp::update() {
//  ofBackground(100, 100, 100);
//
//  bool bNewFrame = false;
//
//#ifdef _USE_LIVE_VIDEO
//  vidGrabber.update();
//  bNewFrame = vidGrabber.isFrameNew();
//#else
//  vidPlayer.update();
//  bNewFrame = vidPlayer.isFrameNew();
//#endif
//
//  if (bNewFrame) {
//
//#ifdef _USE_LIVE_VIDEO
//    colorImg.setFromPixels(vidGrabber.getPixels());
//#else
//    colorImg.setFromPixels(vidPlayer.getPixels());
//#endif
//
//    grayImage = colorImg;
//    if (bLearnBakground == true) {
//      grayBg = grayImage; // the = sign copys the pixels from grayImage into
//                          // grayBg (operator overloading)
//      bLearnBakground = false;
//    }
//
//    // take the abs value of the difference between background and incoming
//    and
//    // then threshold:
//    grayDiff.absDiff(grayBg, grayImage);
//    grayDiff.threshold(threshold);
//
//    // find contours which are between the size of 20 pixels and 1/3 the w*h
//    // pixels.
//    // also, find holes is set to true so we will get interior contours as
//    // well....
//    contourFinder.findContours(grayDiff, 20, (340 * 240) / 3, 10,
//                               true); // find holes
//  }
//
//  for (int i = 0; i < contourFinder.nBlobs; i++) {
//    if (contourFinder.blobs[i].hole) {
//      ofLogNotice() << contourFinder.blobs[0].boundingRect.getCenter().x,
//          contourFinder.blobs[0].boundingRect.getCenter().y;
//    }
//  }
//}
//
////--------------------------------------------------------------
// void ofApp::draw() {
//
//  // draw the incoming, the grayscale, the bg and the thresholded difference
//  ofSetHexColor(0xffffff);
//  colorImg.draw(20, 20);
//  grayImage.draw(360, 20);
//  grayBg.draw(20, 280);
//  grayDiff.draw(360, 280);
//
//  // then draw the contours:
//
//  ofFill();
//  ofSetHexColor(0x333333);
//  ofDrawRectangle(360, 540, 320, 240);
//  ofSetHexColor(0xffffff);
//
//  // we could draw the whole contour finder
//  // contourFinder.draw(360,540);
//
//  // or, instead we can draw each blob individually from the blobs vector,
//  // this is how to get access to them:
//  for (int i = 0; i < contourFinder.nBlobs; i++) {
//    contourFinder.blobs[i].draw(360, 540);
//
//    // draw over the centroid if the blob is a hole
//    ofSetColor(255);
//    if (contourFinder.blobs[i].hole) {
//      ofDrawBitmapString(
//          "hole", contourFinder.blobs[i].boundingRect.getCenter().x + 360,
//          contourFinder.blobs[i].boundingRect.getCenter().y + 540);
//    }
//  }
//
//  // finally, a report:
//  ofSetHexColor(0xffffff);
//  stringstream reportStr;
//  reportStr << "bg subtraction and blob detection" << endl
//            << "press ' ' to capture bg" << endl
//            << "threshold " << threshold << " (press: +/-)" << endl
//            << "num blobs found " << contourFinder.nBlobs
//            << ", fps: " << ofGetFrameRate();
//  ofDrawBitmapString(reportStr.str(), 20, 600);
//}
//
////--------------------------------------------------------------
// void ofApp::keyPressed(int key) {
//
//  switch (key) {
//  case ' ':
//    bLearnBakground = true;
//    break;
//  case '+':
//    threshold++;
//    if (threshold > 255)
//      threshold = 255;
//    break;
//  case '-':
//    threshold--;
//    if (threshold < 0)
//      threshold = 0;
//    break;
//  }
//}
//
////--------------------------------------------------------------
// void ofApp::keyReleased(int key) {}
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
//
