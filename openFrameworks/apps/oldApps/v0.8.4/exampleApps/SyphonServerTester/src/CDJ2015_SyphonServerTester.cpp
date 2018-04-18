#include "CDJ2015_SyphonServerTester.h"

//--------------------------------------------------------------
void CDJ2015_SyphonServerTester::setup(){

    int stageWidth = (RECT_WIDTH*RECT_TOTAL) + (BLANK_SPACE*BLANK_TOTAL);
    
    ofSetWindowTitle("server");
    ofSetWindowShape(stageWidth, TEXTURE_ALLOCATE_HEIGHT*4);
    
    // server
    _server1 = new ofxSyphonServer();
    _server2 = new ofxSyphonServer();
    _server3 = new ofxSyphonServer();
    _server1->setName(SERVER_NAME_1);
    _server2->setName(SERVER_NAME_2);
    _server3->setName(SERVER_NAME_3);
    
    // texture
    _tex1 = new ofTexture();
    _tex2 = new ofTexture();
    _tex3 = new ofTexture();
    _tex1->allocate(RECT_WIDTH,RECT_HEIGHT,GL_RGBA);
    _tex2->allocate(RECT_WIDTH,RECT_HEIGHT,GL_RGBA);
    _tex3->allocate(RECT_WIDTH,RECT_HEIGHT,GL_RGBA);
    
    // position
    _pos_tex1 = ofPoint(0,0);
    _pos_tex2 = ofPoint(RECT_WIDTH+BLANK_SPACE,0);
    _pos_tex3 = ofPoint(RECT_WIDTH*2+BLANK_SPACE*2,0);
}

//--------------------------------------------------------------
void CDJ2015_SyphonServerTester::update(){

    _tex1->loadScreenData(_pos_tex1.x, _pos_tex1.y, RECT_WIDTH, RECT_HEIGHT);
    _tex2->loadScreenData(_pos_tex2.x, _pos_tex2.y, RECT_WIDTH, RECT_HEIGHT);
    _tex3->loadScreenData(_pos_tex3.x, _pos_tex3.y, RECT_WIDTH, RECT_HEIGHT);
}

//--------------------------------------------------------------
void CDJ2015_SyphonServerTester::draw(){
    
    // 1
    ofSetColor(255, 0, 0, cos(ofGetElapsedTimef()*2.0)*127+127);
    ofFill();
    ofRect(_pos_tex1, RECT_WIDTH, RECT_HEIGHT);
    
    // 2
    ofSetColor(0, 255, 0, cos(ofGetElapsedTimef()*4.0)*127+127);
    ofFill();
    ofRect(_pos_tex2, RECT_WIDTH, RECT_HEIGHT);
    
    // 3
    ofSetColor(0, 0, 255, cos(ofGetElapsedTimef()*6.0)*127+127);
    ofFill();
    ofRect(_pos_tex3, RECT_WIDTH, RECT_HEIGHT);
    
    if(GUIDE)
    {
        ofSetColor(0);
        ofNoFill();
        ofRect(_pos_tex1, RECT_WIDTH, RECT_HEIGHT);
        ofRect(_pos_tex2, RECT_WIDTH, RECT_HEIGHT);
        ofRect(_pos_tex3, RECT_WIDTH, RECT_HEIGHT);
    }
    
    // dest
    _server1->publishTexture(_tex1);
    _server2->publishTexture(_tex2);
    _server3->publishTexture(_tex3);
    
    ofSetColor(0);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofPoint(10,ofGetHeight()-10));
}

//--------------------------------------------------------------
void CDJ2015_SyphonServerTester::keyReleased(int key){

}

//--------------------------------------------------------------
void CDJ2015_SyphonServerTester::mouseReleased(int x, int y, int button){

    GUIDE = !GUIDE;
}
