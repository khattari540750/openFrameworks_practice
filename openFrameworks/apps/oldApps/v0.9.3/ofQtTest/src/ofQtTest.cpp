#include "ofQtTest.hpp"

//--------------------------------------------------------------
void ofQtTest::setup(){
    ofSetVerticalSync(true);

    // we add this listener before setting up so the initial circle resolution is correct
    circleResolution.addListener(this, &ofQtTest::circleResolutionChanged);
    ringButton.addListener(this, &ofQtTest::ringButtonPressed);

    gui.setup(); // most of the time you don't need a name
    gui.add(filled.setup("fill", true));
    gui.add(radius.setup("radius", 140, 10, 300));
    gui.add(center.setup("center", ofVec2f(ofGetWidth()*.5, ofGetHeight()*.5), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));
    gui.add(color.setup("color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(circleResolution.setup("circle res", 5, 3, 90));
    gui.add(twoCircles.setup("two circles"));
    gui.add(ringButton.setup("ring"));
    gui.add(screenSize.setup("screen size", ofToString(ofGetWidth())+"x"+ofToString(ofGetHeight())));

    bHide = false;

    ring.load("ring.wav");
}

//--------------------------------------------------------------
void ofQtTest::exit(){
    ringButton.removeListener(this, &ofQtTest::ringButtonPressed);
}

//--------------------------------------------------------------
void ofQtTest::circleResolutionChanged(int &circleResolution){
    ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
void ofQtTest::ringButtonPressed(){
    ring.play();
}

//--------------------------------------------------------------
void ofQtTest::update(){
    ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
void ofQtTest::draw(){
    ofBackgroundGradient(ofColor::white, ofColor::gray);

    if(filled){
        ofFill();
    }else{
        ofNoFill();
    }

    ofSetColor(color);
    if(twoCircles){
        ofDrawCircle(center->x-radius*.5, center->y, radius );
        ofDrawCircle(center->x+radius*.5, center->y, radius );
    }else{
        ofDrawCircle((ofVec2f)center, radius );
    }

    // auto draw?
    // should the gui control hiding?
    if(!bHide){
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofQtTest::keyPressed(int key){
    if(key == 'h'){
        bHide = !bHide;
    }
    else if(key == 's'){
        gui.saveToFile("settings.xml");
    }
    else if(key == 'l'){
        gui.loadFromFile("settings.xml");
    }
    else if(key == ' '){
        color = ofColor(255);
    }
}

//--------------------------------------------------------------
void ofQtTest::keyReleased(int key){

}

//--------------------------------------------------------------
void ofQtTest::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofQtTest::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofQtTest::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofQtTest::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofQtTest::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofQtTest::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofQtTest::windowResized(int w, int h){
    screenSize = ofToString(w) + "x" + ofToString(h);
}

//--------------------------------------------------------------
void ofQtTest::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofQtTest::dragEvent(ofDragInfo dragInfo){

}
