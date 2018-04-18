//
//  drone.cpp
//  frocking
//
//  Created by 服部 弘平 on 2016/03/28.
//
//

#include "drone.hpp"



























/*
//==============================================================
//
//==============================================================
ofxTLDrone::ofxTLDrone()
{
    _bodyObj = new ofBoxPrimitive();
    for(int i=0; i<4; i++) _motorObjs[i] = new ofCylinderPrimitive();
    for(int i=0; i<4; i++) _flapObjs[i] = new ofCylinderPrimitive();
    for(int i=0; i<2; i++) _armObjs[i] = new ofBoxPrimitive();
}


//--------------------------------------------------------------
ofxTLDrone::~ofxTLDrone()
{
    if(_bodyObj) delete _bodyObj;
    for(int i=0; i<4; i++) if(_motorObjs[i]) delete _motorObjs[i];
    for(int i=0; i<4; i++) if(_flapObjs[i]) delete _flapObjs[i];
    for(int i=0; i<2; i++) if(_armObjs[i]) delete _armObjs[i];
}



//==============================================================
//
//==============================================================
void ofxTLDrone::setup()
{
    _bodyColor = ofColor(200,200,200);
    _motorsColor = ofColor(200,200,200);
    _flapsColor = ofColor(200,200,200);
    _armColor = ofColor(200,200,200);
}


//--------------------------------------------------------------
void ofxTLDrone::update()
{
    
}


//--------------------------------------------------------------
void ofxTLDrone::draw()
{
    drawBodyObject();
    drawMotorObjects();
    drawFlapObjects();
    drawArmObjects();
}



//==============================================================
//
//==============================================================
void ofxTLDrone::drawBodyObject()
{
    ofPushMatrix();
    ofSetColor(_bodyColor);
    ofTranslate(0, 0, 0);
    _bodyObj->draw();
    ofPopMatrix();
}


//--------------------------------------------------------------
void ofxTLDrone::drawMotorObjects()
{
    ofPushMatrix();
    ofTranslate(10, 0, 0);
    //_motorsObj->draw();
    ofPopMatrix();
}


//--------------------------------------------------------------
void ofxTLDrone::drawFlapObjects()
{
    ofPushMatrix();
    
    //_flapsObj->draw();
    ofPopMatrix();
}


//--------------------------------------------------------------
void ofxTLDrone::drawArmObjects()
{
    ofPushMatrix();
    
    //_armObj->draw();
    ofPopMatrix();
}
*/