#pragma once



#include "ofMain.h"
#include "ofxOpenCv.h"



class ICP3DTest : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();


private:
    double toRadian(double degree);
    cv::Mat motionEstimationSVD(cv::Mat baseData, cv::Mat fixData);
    double findNearestPoint(cv::Mat baseData, cv::Mat fixData);
    cv::Mat calcICPMatching(cv::Mat baseData, cv::Mat fixData);
    
    
public:
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
    

private:
    cv::Mat _drawBaseData;
    cv::Mat _drawMeasurementData;
    cv::Mat _drawFixData;
    bool _fixFlag;
    ofEasyCam *_cam;
    vector<ofSpherePrimitive> _baseDataObj;
    vector<ofSpherePrimitive> _measurementDataObj;
    vector<ofSpherePrimitive> _fixDataObj;
};