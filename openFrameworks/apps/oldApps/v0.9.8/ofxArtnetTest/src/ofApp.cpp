#include "ofApp.h"

//--------------------------------------------------------------
ofApp::ofApp() {
  //  for (int i = 0; i < 2; i++) {
  //    ofxArtnet *artnet = new ofxArtnet();
  //    artnetList.push_back(artnet);
  //  }
}

//--------------------------------------------------------------
ofApp::~ofApp() {
  //  for (int i = 0; i < artnetList.size(); i++) {
  //    delete artnetList[i];
  //  }
  //  artnetList.clear();
}

//--------------------------------------------------------------
void ofApp::setup() {
  // at first you must specify the Ip address of this machine
  artnet.setup("192.168.11.6"); // make sure the firewall is deactivated at this point

  ofSetFrameRate(40);
  fbo.allocate(512, 1, GL_RGB);

  //  artnetList[0]->setup(
  //      "192.168.11.6"); // make sure the firewall is deactivated at this
  //      point
  //  ofSetFrameRate(40);
  //  fbo.allocate(512, 1, GL_RGB);

  //  // window setup
  //  ofSetFrameRate(40);
  //
  //  // artnet setup
  //  string interfaceIP = "192.168.11.6";
  //  int port1 = 8810;
  //  int port2 = 8820;
  //  int verbose1 = 0;
  //  int verbose2 = 0;
  //  artnetList[0]->setup(interfaceIP.c_str(), port1, verbose1);
  //  artnetList[1]->setup(interfaceIP.c_str(), port2, verbose2);
  //
  //  // gui setup
  //  ofSetVerticalSync(true);
  //  gui.setup();
  //  gui.add(slider.setup("slider", 100, 0, 255));
}

//--------------------------------------------------------------
void ofApp::update() {
  
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
    
    //create send buffer by ofFbo
    {
        fbo.begin();
        ofClear(0);
        float colorR = (sin(ofGetElapsedTimeMillis() / 1000.f) / 2.f + 0.5f) * 255.f;
        float colorG = (sin((ofGetElapsedTimeMillis() / 1000.f) + PI / 3.f) / 2.f + 0.5f) * 255.f;
        float colorB = (sin((ofGetElapsedTimeMillis() / 1000.f)  + PI * 2.f / 3.f) / 2.f + 0.5f) * 255.f;
        ofSetColor((int)colorR, (int)colorG, (int)colorB);
        ofRect(0, 0, 512, 1);
        fbo.end();
        fbo.readToPixels(testImage.getPixelsRef());
    }
    
    //list nodes for sending
    //with subnet / universe
    //    artnet.sendDmx("10.0.0.149", 0xf, 0xf, testImage.getPixels(), 512);
    
    unsigned char dataDmxBase[512];
    for (int i = 0; i < 512; i++) dataDmxBase[i] = 100;
    
    artnet.sendDmx("192.168.11.4", dataDmxBase, 512);
    artnet.sendDmx("192.168.11.5", dataDmxBase, 512);
    
    
    
    

  //  ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
  //  cout << slider << endl;
  //
  //  string targetIP1 = "192.168.11.4";
  //  string targetIP2 = "192.168.11.5";
  //  int targetSubnet1 = 0;
  //  int targetSubnet2 = 0;
  //  int targetUniverse1 = 0;
  //  int targetUniverse2 = 0;
  //  int size = 512;
  //
  //  unsigned char dataDmxBase[512];
  //  for (int i = 0; i < 512; i++)
  //    dataDmxBase[i] = 0;
  //  dataDmxBase[9] = (unsigned int)slider;
  //
  //  artnetList[0]->sendDmx(targetIP1, dataDmxBase, size);
  //  artnetList[1]->sendDmx(targetIP2, dataDmxBase, size);
  //  // artnetList[0]->sendDmx("192.168.11.2", 0, 512);
  //  // artnetList[1]->sendDmx("192.168.11.3", 0, 512);
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofBackground(0);
  float scalex = ofGetWidth() / fbo.getWidth();
  float scaley = ofGetHeight() / fbo.getHeight();
  ofScale(scalex, scaley);
  fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

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
