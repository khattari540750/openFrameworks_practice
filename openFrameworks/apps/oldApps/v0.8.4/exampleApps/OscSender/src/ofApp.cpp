#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    sender.setup(HOST, PORT);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255);
    ofCircle(mouseX, mouseY, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    ofxOscMessage m;
    m.setAddress("/mouse/position");
    m.addIntArg(x);
    m.addIntArg(y);
    sender.sendMessage(m);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ofxOscMessage m;
    m.setAddress("/mouse/position");
    m.addStringArg("down");
    sender.sendMessage(m);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    ofxOscMessage m;
    m.setAddress("/mouse/button");
    m.addStringArg("up");
    sender.sendMessage(m);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
