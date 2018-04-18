//
//  example_sharpyConcentration.cpp
//  example_sharpyConcentration
//
//  Created by HATTORI Kohei on 2016/02/29.
//
//



#include "example_sharpyConcentration.h"



//==============================================================
// of basic functions
//==============================================================
void example_sharpyConcentration::setup()
{
    // load moving & target parameter from xml
    _xmlController.loadMovingHeadLightParameterXML("movingHeadLightConcentration.xml");
    winp windowParameter = _xmlController.getWindowParamter();
    vector<mhlp> movingHeadLightList = _xmlController.getMovingHeadLightParameterList();
    vector<ofVec3f> targetPosList = _xmlController.getConcentrationPointList();
    

    // window setup
    ofSetWindowTitle(windowParameter.windowName);
    ofSetWindowShape(windowParameter.windowSizeWidth, windowParameter.windowSizeHeight);
    ofBackground(170);
    
    
    // camera setPosition ( X>Y>Z coordinate )
    _cam.setDistance(windowParameter.cameraDistance);
    _cam.setFarClip(windowParameter.cameraFarClip);
    _cam.setPosition(windowParameter.cameraPosX, windowParameter.cameraPosY, windowParameter.cameraPosZ);
    _cam.lookAt(ofVec3f(0, 0, -1));
    
    
    // sharpy setup (set position)
    for(int i=0; i<movingHeadLightList.size(); i++){
        ofxMovingHeadLightSharpy* sharpy = new ofxMovingHeadLightSharpy;
        _sharpyList.push_back(sharpy);
        _sharpyList[i]->setup();
        _sharpyList[i]->setName(movingHeadLightList[i].name);
        cout << _sharpyList[i]->getName() << endl;
        _sharpyList[i]->setStartChannel(movingHeadLightList[i].startChannel);
        _sharpyList[i]->setPositionRotate(movingHeadLightList[i].posX, movingHeadLightList[i].posY, movingHeadLightList[i].posZ,
                                          movingHeadLightList[i].rotX, movingHeadLightList[i].rotY, movingHeadLightList[i].rotZ);
    }
    
    
    // moving head light DMX manager setup
    for(int i=0; i<_sharpyList.size(); i++) _manager.setMovingHeadLightModel(_sharpyList[i]);
    _manager.setDevice(_xmlController.getDMXDeviceName());
    _manager.startCommunicate();
    
    
    // target setup
    for(int i=0; i<targetPosList.size(); i++){
        ofVec3f* targetPos = new ofVec3f;
        _targetPosList.push_back(targetPos);
        *_targetPosList[i] = targetPosList[i];
        
        ofSpherePrimitive* targetPointObj = new ofSpherePrimitive;
        _targetPointObjList.push_back(targetPointObj);
        _targetPointObjList[i]->set(50,50);
    }
    
    
    // select moving head light panel setup
    ofSetVerticalSync(true);
    _selectMovingHeadLightPanel.setDefaultWidth(200);
    _selectMovingHeadLightPanel.setup("moving head light");
    _selectMovingHeadLightPanel.add(_slctMhlNum.set("moving head light num", 0, 0, _sharpyList.size()-1));
    _selectMovingHeadLightPanel.setPosition(ofGetWindowWidth()-_selectMovingHeadLightPanel.getWidth()-10,
                                            ofGetWindowHeight()-_selectMovingHeadLightPanel.getHeight()-10);
    
    // select target panel setup
    ofSetVerticalSync(true);
    _selectTargetPanel.setDefaultWidth(200);
    _selectTargetPanel.setup("target");
    _selectTargetPanel.add(_slctTrgtNum.set("target num", 0, 0, _targetPosList.size()-1));
    ofPoint selectTargetPanelPos = _selectMovingHeadLightPanel.getPosition();
    selectTargetPanelPos.y -= _selectTargetPanel.getHeight()+5;
    _selectTargetPanel.setPosition(selectTargetPanelPos);
    
    
    // controll panel setup
    ofSetVerticalSync(true);
    for(int i=0; i<_sharpyList.size(); i++){
        ofxPanel* controllPanel = new ofxPanel;
        ofParameter<int>* ctrPan = new ofParameter<int>;
        ofParameter<int>* ctrPanFine = new ofParameter<int>;
        ofParameter<int>* ctrTilt = new ofParameter<int>;
        ofParameter<int>* ctrTiltFine = new ofParameter<int>;
        ofxButton* ctrGetPanTiltButton = new ofxButton;
        
        _controlPanelList.push_back(controllPanel);
        _ctrPanValList.push_back(ctrPan);
        _ctrPanFineValList.push_back(ctrPanFine);
        _ctrTiltValList.push_back(ctrTilt);
        _ctrTiltFineValList.push_back(ctrTiltFine);
        _ctrGetPanTiltButtonList.push_back(ctrGetPanTiltButton);
        
        _controlPanelList[i]->setDefaultWidth(700);
        _controlPanelList[i]->setup(movingHeadLightList[i].name + " control");
        _controlPanelList[i]->add(_ctrPanValList[i]->set("Pan", 0, 0, 255));
        _controlPanelList[i]->add(_ctrPanFineValList[i]->set("PanFine", 0, 0, 255));
        _controlPanelList[i]->add(_ctrTiltValList[i]->set("Tilt", 0, 0, 255));
        _controlPanelList[i]->add(_ctrTiltFineValList[i]->set("TiltFine", 0, 0, 255));
        _controlPanelList[i]->add(_ctrGetPanTiltButtonList[i]->setup("get pan tilt value"));
    }
    _preventChatteringTime1 = ofGetElapsedTimeMillis();
    
    
    // get position rotation matrix button panel
    ofSetVerticalSync(true);
    for(int i=0; i<_sharpyList.size(); i++){
        ofxPanel* saveButtonPanel = new ofxPanel;
        ofxButton* saveButton = new ofxButton;
        
        _saveButtonPanelList.push_back(saveButtonPanel);
        _saveButtonList.push_back(saveButton);
        
        _saveButtonPanelList[i]->setDefaultWidth(250);
        _saveButtonPanelList[i]->setup(movingHeadLightList[i].name + " get pos rotation");
        _saveButtonPanelList[i]->add(_saveButtonList[i]->setup("get moving pos"));
        
        ofPoint saveButtonPanelPos = _controlPanelList[i]->getPosition();
        saveButtonPanelPos.y += _controlPanelList[i]->getHeight()+5;
        _saveButtonPanelList[i]->setPosition(saveButtonPanelPos);
    }
    _preventChatteringTime2 = ofGetElapsedTimeMillis();
    _saveButtonPanelFlag = false;
    
    
    // optional controll panel
    ofSetVerticalSync(true);
    for(int i=0; i<_sharpyList.size(); i++){
        ofxPanel* controllOptionPanel = new ofxPanel;
        ofParameter<int>* ctrOptFocus = new ofParameter<int>;
        ofParameter<int>* ctrOptDimmer = new ofParameter<int>;
        ofParameter<int>* ctrOptFrost = new ofParameter<int>;
        ofParameter<ofColor>* ctrOptColorWheel= new ofParameter<ofColor>;
        ofParameter<int>* ctrOptGoboWheel = new ofParameter<int>;
        
        _controlOptionPanelList.push_back(controllOptionPanel);
        _ctrOptFocusValList.push_back(ctrOptFocus);
        _ctrOptDimmerValList.push_back(ctrOptDimmer);
        _ctrOptFrostValList.push_back(ctrOptFrost);
        _ctrOptColorWheelValList.push_back(ctrOptColorWheel);
        _ctrOptGoboWheelValList.push_back(ctrOptGoboWheel);
        
        _controlOptionPanelList[i]->setDefaultWidth(500);
        _controlOptionPanelList[i]->setup(movingHeadLightList[i].name + " option control");
        _controlOptionPanelList[i]->add(_ctrOptFocusValList[i]->set("focus", 0, 0, 255));
        _controlOptionPanelList[i]->add(_ctrOptDimmerValList[i]->set("dimmer", 0, 0, 255));
        _controlOptionPanelList[i]->add(_ctrOptFrostValList[i]->set("frost", 0, 0, 255));
        _controlOptionPanelList[i]->add(_ctrOptColorWheelValList[i]->set("colorWheel", 0, 0, 255));
        _controlOptionPanelList[i]->add(_ctrOptGoboWheelValList[i]->set("goboWheel", 0, 0, 255));
        if(_saveButtonPanelFlag){
            ofPoint controlPanelPos = _saveButtonPanelList[i]->getPosition();
            controlPanelPos.y += _saveButtonPanelList[i]->getHeight()+5;
            _controlOptionPanelList[i]->setPosition(controlPanelPos);
        }
        else {
            ofPoint controlPanelPos = _controlPanelList[i]->getPosition();
            controlPanelPos.y += _controlPanelList[i]->getHeight()+5;
            _controlOptionPanelList[i]->setPosition(controlPanelPos);
        }
    }
    _ctrOptionPanelFlag = true;
    
    
    // old target set
    for(int i=0; i<_sharpyList.size(); i++){
        _oldTargetNumList.push_back(-1);
    }
}


//--------------------------------------------------------------
void example_sharpyConcentration::update()
{
    // target pos check & update
    ofVec3f targetPos = *_targetPosList[_slctTrgtNum];
    _targetPointObjList[_slctTrgtNum]->setPosition(targetPos);
    
    
    if(_oldTargetNumList[_slctMhlNum] != _slctTrgtNum){
        // chase pos
        _sharpyList[_slctMhlNum]->chasePoint((double)targetPos.x, (double)targetPos.y, (double)targetPos.z);
        
        // moving update
        for(int i=0; i<_sharpyList.size(); i++) _sharpyList[i]->update();
        _manager.update();
        
        // panel update
        *_ctrPanValList[_slctMhlNum] = _sharpyList[_slctMhlNum]->getPan();
        *_ctrPanFineValList[_slctMhlNum] = _sharpyList[_slctMhlNum]->getPanFine();
        *_ctrTiltValList[_slctMhlNum] = _sharpyList[_slctMhlNum]->getTilt();
        *_ctrTiltFineValList[_slctMhlNum] = _sharpyList[_slctMhlNum]->getTiltFine();
        
        //old target num update
        _oldTargetNumList[_slctMhlNum] = _slctTrgtNum;
    }
    else {
        // control panel update only selected
        _sharpyList[_slctMhlNum]->changePan(*_ctrPanValList[_slctMhlNum]);
        _sharpyList[_slctMhlNum]->changePanFine(*_ctrPanFineValList[_slctMhlNum]);
        _sharpyList[_slctMhlNum]->changeTilt(*_ctrTiltValList[_slctMhlNum]);
        _sharpyList[_slctMhlNum]->changeTiltFine(*_ctrTiltFineValList[_slctMhlNum]);
        
        // control option panel update only selected
        _sharpyList[_slctMhlNum]->changeFocus(*_ctrOptFocusValList[_slctMhlNum]);
        _sharpyList[_slctMhlNum]->changeDimmer(*_ctrOptDimmerValList[_slctMhlNum]);
        _sharpyList[_slctMhlNum]->changeFrost(*_ctrOptFrostValList[_slctMhlNum]);
        _sharpyList[_slctMhlNum]->changeColorWheel(*_ctrOptColorWheelValList[_slctMhlNum]);
        _sharpyList[_slctMhlNum]->changeGoboWheel(*_ctrOptGoboWheelValList[_slctMhlNum]);
        
        // get pan tilt val bunnton
        if(*_ctrGetPanTiltButtonList[_slctMhlNum]){
            unsigned int diffTime = ofGetElapsedTimeMillis() - _preventChatteringTime1;
            if(diffTime > 1000){
                
                // set values
                string name = _sharpyList[_slctMhlNum]->getName();
                unsigned int pan = _sharpyList[_slctMhlNum]->getPan();
                unsigned int panFine = _sharpyList[_slctMhlNum]->getPanFine();
                unsigned int tilt = _sharpyList[_slctMhlNum]->getTilt();
                unsigned int tiltFine = _sharpyList[_slctMhlNum]->getTiltFine();
                cout << "[example_sharpyConcentration] pan = " << pan << endl;
                cout << "[example_sharpyConcentration] panFine = " << panFine << endl;
                cout << "[example_sharpyConcentration] tilt = " << tilt << endl;
                cout << "[example_sharpyConcentration] tiltFine = " << tiltFine << endl;
                _xmlController.setPanTiltVal(name, pan, panFine, tilt, tiltFine);
                
                // change panel color
                _controlPanelList[_slctMhlNum]->setTextColor(ofColor(255,0,0));
                _controlOptionPanelList[_slctMhlNum]->setTextColor(ofColor(255,0,0));
                
                // time update
                _preventChatteringTime1 = ofGetElapsedTimeMillis();
            }
        }
        
        // get rotation matrix button
        if(*_saveButtonList[_slctMhlNum]){
            unsigned int diffTime = ofGetElapsedTimeMillis() - _preventChatteringTime2;
            if(diffTime > 1000){
                string fileName = _xmlController.getSaveFileName();
                _xmlController.savePanTiltValXML(fileName);
                cout << "[example_sharpyConcentration] file save now! : " << fileName << endl;
                _preventChatteringTime2 = ofGetElapsedTimeMillis();
            }
        }
        
        // moving update
        for(int i=0; i<_sharpyList.size(); i++) _sharpyList[i]->update();
        _manager.update();
    }
}


//--------------------------------------------------------------
void example_sharpyConcentration::draw()
{
    _cam.begin();
    
    // drow moving head lights
    for(int i=0; i<_sharpyList.size(); i++){
        if(i==_slctMhlNum){
            _sharpyList[i]->setBodyColor(ofColor(0, 100));
            _sharpyList[i]->setMonitorColor(ofColor(255, 180, 0, 200));
        }
        else {
            _sharpyList[i]->setBodyColor(ofColor(0, 10));
            _sharpyList[i]->setMonitorColor(ofColor(255, 180, 0, 20));
        }
        _sharpyList[i]->draw();
    }
    
    // draw target points
    for(int i=0; i<_targetPointObjList.size(); i++){
        if(i==_slctTrgtNum) ofSetColor(255, 255, 0, 255);
        else ofSetColor(255, 255, 0, 20);
        _targetPointObjList[i]->draw();
    }
    
    // draw axis
    ofDrawAxis(300);
    _cam.end();
    
    
    // panels
    if(_saveButtonPanelFlag){
        ofPoint controlPanelPos = _saveButtonPanelList[_slctMhlNum]->getPosition();
        controlPanelPos.y += _saveButtonPanelList[_slctMhlNum]->getHeight()+5;
        _controlOptionPanelList[_slctMhlNum]->setPosition(controlPanelPos);
    }
    else {
        ofPoint controlPanelPos = _controlPanelList[_slctMhlNum]->getPosition();
        controlPanelPos.y += _controlPanelList[_slctMhlNum]->getHeight()+5;
        _controlOptionPanelList[_slctMhlNum]->setPosition(controlPanelPos);
    }
    _controlPanelList[_slctMhlNum]->draw();
    if(_saveButtonPanelFlag) _saveButtonPanelList[_slctMhlNum]->draw();
    if(_ctrOptionPanelFlag) _controlOptionPanelList[_slctMhlNum]->draw();
    _selectMovingHeadLightPanel.draw();
    _selectTargetPanel.draw();
    
    
    // FPS draw
    ofSetColor(255);
    ofDrawBitmapString("FPS : " + ofToString(ofGetFrameRate()), ofPoint(10, ofGetWindowHeight()-10));
}



//==============================================================
// of utility functions
//==============================================================
void example_sharpyConcentration::keyPressed(int key)
{
    if(key == 'o'){
        _ctrOptionPanelFlag = !_ctrOptionPanelFlag;
    }
    else if(key == 'r') {
        _saveButtonPanelFlag = !_saveButtonPanelFlag;
    }
}


//--------------------------------------------------------------
void example_sharpyConcentration::keyReleased(int key)
{
    
}


//--------------------------------------------------------------
void example_sharpyConcentration::mouseMoved(int x, int y )
{
    
}


//--------------------------------------------------------------
void example_sharpyConcentration::mouseDragged(int x, int y, int button)
{
    
}


//--------------------------------------------------------------
void example_sharpyConcentration::mousePressed(int x, int y, int button)
{
    
}


//--------------------------------------------------------------
void example_sharpyConcentration::mouseReleased(int x, int y, int button)
{
    
}


//--------------------------------------------------------------
void example_sharpyConcentration::mouseEntered(int x, int y)
{
    
}


//--------------------------------------------------------------
void example_sharpyConcentration::mouseExited(int x, int y)
{
    
}


//--------------------------------------------------------------
void example_sharpyConcentration::windowResized(int w, int h)
{
    
}


//--------------------------------------------------------------
void example_sharpyConcentration::gotMessage(ofMessage msg)
{
    
}


//--------------------------------------------------------------
void example_sharpyConcentration::dragEvent(ofDragInfo dragInfo)
{
    
}