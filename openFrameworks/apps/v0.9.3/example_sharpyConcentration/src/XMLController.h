//
//  XMLController.h
//  example_sharpyConcentration
//
//  Created by HATTORI Kohei on 2016/03/01.
//
//

#ifndef __example_sharpyConcentration__XMLController__
#define __example_sharpyConcentration__XMLController__



#include "ofMain.h"



typedef struct windowParamter
{
    string windowName;
    unsigned int windowSizeWidth;
    unsigned int windowSizeHeight;
    float cameraDistance;
    float cameraFarClip;
    float cameraPosX;
    float cameraPosY;
    float cameraPosZ;
} winp;



typedef struct movingHeadLightParameter
{
    string name;
    unsigned int startChannel;
    double posX, posY, posZ;
    double rotX, rotY, rotZ;
} mhlp;



class XMLController
{
public: // load & save
    void loadMovingHeadLightParameterXML(string fileName);
    void savePanTiltValXML(string fileName);
  
    
public: // get & set
    winp getWindowParamter();
    string getDMXDeviceName();
    string getSaveFileName();
    vector<mhlp> getMovingHeadLightParameterList();
    vector<ofVec3f> getConcentrationPointList();
    void setPanTiltVal(string name, unsigned int pan,  unsigned int panFine,
                       unsigned int tilt, unsigned int tiltFine);
 
    
private: // struct only use this class
    typedef struct movingHeadLightpanTiltValue
    {
        unsigned int pan;
        unsigned int panFine;
        unsigned int tilt;
        unsigned int tiltFine;
    } ptv;

    
private: // instance
    ofXml _xml;
    
    winp _windowParameter;
    string _DMXDeviceName;
    string _saveFileName;
    
    vector<mhlp> _movingHeadLightParameterList;
    vector<ofVec3f> _concentrationPointList;
    
    vector<string> _nameList;
    map<string, ptv> _valList;
};



#endif