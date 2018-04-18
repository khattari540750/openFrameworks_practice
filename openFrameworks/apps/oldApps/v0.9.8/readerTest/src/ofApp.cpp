#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofxXmlSettings xml;
  xml.loadFile("test.xml");
}

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {}

void DataReader::loadXml(string path) {
  ofxXmlSettings xml;
  xml.loadFile(path);
}