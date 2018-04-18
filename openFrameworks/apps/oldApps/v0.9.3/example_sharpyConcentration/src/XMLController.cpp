//  XMLController.cpp
//  example_sharpyConcentration
//
//  Created by HATTORI Kohei on 2016/03/01.
//
//


#include "XMLController.h"



//==============================================================
// load & save
//==============================================================
void XMLController::loadMovingHeadLightParameterXML(string fileName)
{
    // load file
    _xml.clear();
    if( _xml.load(fileName) ) cout << fileName << endl;
    
    
    // set application parameters
    if(_xml.exists("windowSetup")){
        _xml.setTo("windowSetup");
        
        if(_xml.exists("windowName")) _windowParameter.windowName = _xml.getValue<string>("windowName");
        if(_xml.exists("windowSizeWidth")) _windowParameter.windowSizeWidth = _xml.getValue<unsigned int>("windowSizeWidth");
        if(_xml.exists("windowSizeHeight")) _windowParameter.windowSizeHeight = _xml.getValue<unsigned int>("windowSizeHeight");
        if(_xml.exists("cameraDistance")) _windowParameter.cameraDistance = _xml.getValue<float>("cameraDistance");
        if(_xml.exists("cameraFarClip")) _windowParameter.cameraFarClip = _xml.getValue<float>("cameraFarClip");
        
        if(_xml.exists("cameraPosX")) _windowParameter.cameraPosX = _xml.getValue<float>("cameraPosX");
        if(_xml.exists("cameraPosY")) _windowParameter.cameraPosY = _xml.getValue<float>("cameraPosY");
        if(_xml.exists("cameraPosZ")) _windowParameter.cameraPosZ = _xml.getValue<float>("cameraPosZ");
        
        _xml.setToParent();
    }
    
    if(_xml.exists("applicationSetup")){
        _xml.setTo("applicationSetup");
        if(_xml.exists("DMXDeviceName")) _DMXDeviceName = _xml.getValue<string>("DMXDeviceName");
        if(_xml.exists("saveFileName")) _saveFileName = _xml.getValue<string>("saveFileName");
        
        _xml.setToParent();
    }
    
    
    // set "concentrationPoint" instance
    if(_xml.exists("concentrationPoint")){
        if(_xml.getName() == "movingHeadLightConcentration" && _xml.setTo("concentrationPoint[0]")) {
            do {
                ofVec3f calibrationPoint;
                if(_xml.exists("posX")) calibrationPoint.x = _xml.getValue<float>("posX");
                if(_xml.exists("posY")) calibrationPoint.y = _xml.getValue<float>("posY");
                if(_xml.exists("posZ")) calibrationPoint.z = _xml.getValue<float>("posZ");
                if(_xml.exists("posX") && _xml.exists("posY")&& _xml.exists("posZ")) {
                    _concentrationPointList.push_back(calibrationPoint);
                }
            } while( _xml.setToSibling() );
            _xml.setToParent();
        }
    }
    
    
    // get moving head light parameters
    if(_xml.exists("movingHeadLight")){
        if(_xml.getName() == "movingHeadLightConcentration" && _xml.setTo("movingHeadLight[0]")) {
            do {
                mhlp loadParam;
                if(_xml.exists("name")) loadParam.name = _xml.getValue<string>("name");
                if(_xml.exists("startChannel")) loadParam.startChannel = _xml.getValue<int>("startChannel");
                if(_xml.exists("position")){
                    _xml.setTo("position");
                    loadParam.posX = _xml.getValue<float>("posX");
                    loadParam.posY = _xml.getValue<float>("posY");
                    loadParam.posZ = _xml.getValue<float>("posZ");
                    loadParam.rotX = _xml.getValue<float>("rotX");
                    loadParam.rotY = _xml.getValue<float>("rotY");
                    loadParam.rotZ = _xml.getValue<float>("rotZ");
                    _xml.setToParent();
                }
                _movingHeadLightParameterList.push_back(loadParam);
            } while( _xml.setToSibling() );
            _xml.setToParent();
        }
    }
}


//--------------------------------------------------------------
void XMLController::savePanTiltValXML(string fileName)
{
    // set xml object
    _xml.clear();
    _xml.addChild("movingHeadLightPinpointing");
    _xml.setTo("//movingHeadLightPinpointing");
    
    
    // set values
    map<string, ptv>::iterator itr = _valList.begin();
    while(itr != _valList.end()){
        ofXml moving;
        moving.addChild("movingHeadLight");
        moving.setTo("movingHeadLight");
        
        moving.addValue("pan", (*itr).second.pan);
        moving.addValue("panFine", (*itr).second.panFine);
        moving.addValue("tilt", (*itr).second.tilt);
        moving.addValue("tiltFine", (*itr).second.tiltFine);
        _xml.addXml(moving);
        itr++;
    }
    
    
    // save to xml file
    _xml.save(fileName);
}



//==============================================================
// get & set
//==============================================================
winp XMLController::getWindowParamter()
{
    return _windowParameter;
}


//--------------------------------------------------------------
string XMLController::getDMXDeviceName()
{
    return _DMXDeviceName;
}


//--------------------------------------------------------------
string XMLController::getSaveFileName()
{
    return _saveFileName;
}


//--------------------------------------------------------------
vector<mhlp> XMLController::getMovingHeadLightParameterList()
{
    return _movingHeadLightParameterList;
}


//--------------------------------------------------------------
vector<ofVec3f> XMLController::getConcentrationPointList()
{
    return _concentrationPointList;
}


//--------------------------------------------------------------
void XMLController::setPanTiltVal(string name, unsigned int pan,  unsigned int panFine,
                                  unsigned int tilt, unsigned int tiltFine)
{
    // set values (use to C++ map)
    ptv val;
    val.pan = pan;
    val.panFine = panFine;
    val.tilt = tilt;
    val.tiltFine = tiltFine;
    _valList[name] = val;
}