#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "matrix.h"




class testApp : public ofBaseApp
{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    
    
private:
    bool data3Flag;
    
    

    //ofVideoGrabber 		vidGrabber;
    //ofxCvColorImage colorImg;
    //ofxCvGrayscaleImage grayImage;
    //ofxCvGrayscaleImage grayBg;
    //ofxCvGrayscaleImage grayDiff;
    //ofxCvContourFinder contourFinder;
    
    //bool bLearnBakground;
    //bool showCvAnalysis;
    //int threshold;
    //int videoMode;
};




class movingLight
{
public:
    movingLight();
    ~movingLight();
    
    double inverseKineticsPan(double x, double y);
    double inverseKineticsTilt(double x, double y, double z);
    double inverseKineticsOpticalAxis(double x, double y, double z);
    
    cv::Mat ICPMatching(cv::Mat before, cv::Mat after);
    
    
private:
    double l0, l1, l2;
};







class ICPMatching
{
    void setPointData(cv::Mat before, cv::Mat after);
    void calc();
    cv::Mat get_R();
    cv::Mat get_t();
    cv::Mat get_Rt();
    
    
private:
    double findNearestPoint(cv::Mat before, cv::Mat after);
    void SVDMotionEstimation(cv::Mat before, cv::Mat after);
    

private:
    cv::Mat R;
    cv::Mat t;
};





#endif