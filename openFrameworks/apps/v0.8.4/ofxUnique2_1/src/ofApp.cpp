#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(220, 200);
    
    _unique2_1 = new ofxUnique2_1();
    _unique2_1->setup("/dev/tty.usbserial-EN167919",1);
    _unique2_1->set_startChannel(1, 1);
    _unique2_1->communicateStart();
    
    _gui = new ofxPanel();
    _gui->setup();
    _gui->add(_param_ch1.set("ch1 pump", 255, 0, 255));
    _gui->add(_param_ch2.set("ch2 fan", 255, 0, 255));
}

//--------------------------------------------------------------
void ofApp::update(){
    _unique2_1->update();
    
    _unique2_1->change_pump(1, _param_ch1);
    _unique2_1->change_fan(1, _param_ch2);
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofPoint(10,ofGetHeight()-20));
    _gui->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
