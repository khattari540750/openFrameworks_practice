//
//  example_sharpyConcentration.h
//  example_sharpyConcentration
//
//  Created by HATTORI Kohei on 2016/02/29.
//
//

#pragma once



#include "ofMain.h"
#include "ofxGui.h"
#include "ofxMovingHeadLight.h"
#include "XMLController.h"



class example_sharpyConcentration : public ofBaseApp
{
public: // of basic functions
    void setup();
    void update();
    void draw();
    
    
public: // of utility functions
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    

private: // functional object variables
    ofEasyCam _cam;
    XMLController _xmlController;
    ofxMovingHeadLightManager _manager;
    vector<ofxMovingHeadLightSharpy*> _sharpyList;
    
    
private: // concentration target point variables
    vector<ofSpherePrimitive*> _targetPointObjList;
    vector<ofVec3f*> _targetPosList;
    vector<int> _oldTargetNumList;
 
    
private: // select moving head light panel variables
    ofxPanel _selectMovingHeadLightPanel;
    ofParameter<int> _slctMhlNum;
    
    
private: // select target panel variables
    ofxPanel _selectTargetPanel;
    ofParameter<int> _slctTrgtNum;
    
    
private: // moving head light control panel variables
    vector<ofxPanel*> _controlPanelList;
    vector<ofParameter<int>*> _ctrPanValList;
    vector<ofParameter<int>*> _ctrPanFineValList;
    vector<ofParameter<int>*> _ctrTiltValList;
    vector<ofParameter<int>*> _ctrTiltFineValList;
    vector<ofxButton*> _ctrGetPanTiltButtonList;
    unsigned int _preventChatteringTime1;
    
    
private: // moving head light get position rotation matrix panel variables
    vector<ofxPanel*> _saveButtonPanelList;
    vector<ofxButton*> _saveButtonList;
    unsigned int _preventChatteringTime2;
    bool _saveButtonPanelFlag;
    
    
private: //  moving head light  control option panel variables
    vector<ofxPanel*> _controlOptionPanelList;
    vector<ofParameter<int>*> _ctrOptFocusValList;
    vector<ofParameter<int>*> _ctrOptDimmerValList;
    vector<ofParameter<int>*> _ctrOptFrostValList;
    vector<ofParameter<ofColor>*> _ctrOptColorWheelValList;
    vector<ofParameter<int>*> _ctrOptGoboWheelValList;
    bool _ctrOptionPanelFlag;
};
