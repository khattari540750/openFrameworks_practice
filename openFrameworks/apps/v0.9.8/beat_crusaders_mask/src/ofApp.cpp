#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

  // serial
  serial.setup("/dev/tty.usbmodem1411", 9600);

  // grababer
  vidGrabber.setVerbose(true);
  vidGrabber.setup(imageWidth, imageHeight);

  // images
  cameraImage.allocate(imageWidth, imageHeight);
  grayImage.allocate(imageWidth, imageHeight);

  mosaicImage.allocate(imageWidth, imageHeight);
  monoImage.allocate(imageWidth, imageHeight);

  cutImage.allocate(imageWidth, imageHeight, OF_IMAGE_GRAYSCALE);

  gui.setup(); // most of the time you don't need a name
  gui.add(resolution.setup("resolution", 3, 1, 10));
  gui.add(threshold.setup("threshold", 100, 0, 255));

  for (int w = 0; w < imageWidth; w++) {
    for (int h = 0; h < imageHeight; h++) {
      colorList.push_back(ofColor(0, 0, 0));
    }
  }
}

//--------------------------------------------------------------
void ofApp::update() {
  ofBackground(100, 100, 100);

  bool bNewFrame = false;
  vidGrabber.update();
  bNewFrame = vidGrabber.isFrameNew();

  if (bNewFrame) {
    cameraImage.setFromPixels(vidGrabber.getPixels());
    grayImage = cameraImage;

    mosaicImage = grayImage;
    monoImage = mosaicImage;
    monoImage.threshold(threshold);

    ofPixels pixels = monoImage.getPixels();
    int i = 0;
    for (int w = 0; w < pixels.getWidth(); w++) {
      for (int h = 0; h < pixels.getHeight(); h++) {
        colorList[i] = pixels.getColor(w, h);
        i++;
      }
    }
    cutImage.setFromPixels(pixels);

    unsigned char buf[513];
    for (int i = 0; i < colorList.size(); i++) {
      if (colorList[i] == ofColor(0, 0, 0)) {
        buf[i] = 0;
      }
      if (colorList[i] == ofColor(255, 255, 255)) {
        buf[i] = 1;
      }
    }
    buf[512] = ';';
    serial.writeBytes(&buf[0], 513);

    //    unsigned char buf[65];
    //    for (int i = 0; i < 65; i++) {
    //      buf[i] = 0b00000000;
    //    }
    //    int eight = 0;
    //    int bufNum = 0;
    //    for (int i = 0; i < colorList.size(); i++) {
    //      unsigned char tmp;
    //      if (colorList[i] == ofColor(0, 0, 0)) {
    //        tmp = 0b00000000;
    //      }
    //      if (colorList[i] == ofColor(255, 255, 255)) {
    //        tmp = 0b00000001;
    //      }
    //      buf[bufNum] << 1;
    //      buf[bufNum] | tmp;
    //
    //      eight++;
    //      if (eight >= 8) {
    //        eight = 0;
    //        bufNum++;
    //      }
    //    }
    //    buf[64] = ';';
    //    serial.writeBytes(&buf[0], 65);
  }
}
//--------------------------------------------------------------
void ofApp::draw() {

  cameraImage.draw(20, 20);
  grayImage.draw(360, 20);

  mosaicImage.draw(20, 300);

  monoImage.draw(360, 300);
  cutImage.draw(700, 20);

  gui.draw();

  int numOfBlack = 0;
  int numOfWhite = 0;
  for (int i = 0; i < colorList.size(); i++) {
    if (colorList[i] == ofColor(0, 0, 0))
      numOfBlack++;
    if (colorList[i] == ofColor(255, 255, 255))
      numOfWhite++;
  }

  ofSetHexColor(0xffffff);
  stringstream reportStr;
  reportStr << "size of width and height" << endl
            << "num of black " << numOfBlack << endl
            << "num of white " << numOfWhite << endl
            << "num of size " << numOfWhite + numOfBlack << endl
            << ", fps: " << ofGetFrameRate();
  ofDrawBitmapString(reportStr.str(), 20, 600);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 'g') {
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

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
