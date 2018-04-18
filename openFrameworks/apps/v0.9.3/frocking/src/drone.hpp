//
//  drone.hpp
//  frocking
//
//  Created by 服部 弘平 on 2016/03/28.
//
//

#ifndef __ofxTLDrone__ofxTLDrone__
#define __ofxTLDrone__ofxTLDrone__



#include "ofMain.h"



class ofxTLDrone
{
public:
    ofxTLDrone();
    ~ofxTLDrone();

    void update();
    void draw();
    
    
private:
    ofBoxPrimitive* _bodyObj;
};















/*
class ofxTLDrone
{
public:
    ofxTLDrone();
    ~ofxTLDrone();
    
    void setup();
    void update();
    void draw();
    
    
private:
    void drawBodyObject();
    void drawMotorObjects();
    void drawFlapObjects();
    void drawArmObjects();
    
    
private:
    ofBoxPrimitive*      _bodyObj;
    ofCylinderPrimitive* _motorObjs[4];
    ofCylinderPrimitive* _flapObjs[4];
    ofBoxPrimitive*      _armObjs[2];
    
    ofColor _bodyColor,  _motorsColor,
            _flapsColor, _armColor;
};
*/


#endif /* drone_hpp */
