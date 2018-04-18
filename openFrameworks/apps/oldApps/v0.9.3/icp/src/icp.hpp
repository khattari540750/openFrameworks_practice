//!
//! @file icp.hpp
//! @brief icp (please use well-known corresponding point)
//! @author HATTORI Kohei
//! @date 4/7/2016
//!

#ifndef icp_hpp
#define icp_hpp

#include "ofMain.h"
#include "ofxOpenCv.h"

class ICP {
    
private:
    struct ofVec3d {
        double x;
        double y;
        double z;
    };
    
public:
    ofMatrix4x4 calcICP();
    void setPoint(ofVec3f basePoint, ofVec3f modifiedPoint);
    
private:
    static cv::Mat motionEstimationSVD(cv::Mat baseData, cv::Mat modifiedData);
    static double findNearestPoint(cv::Mat baseData, cv::Mat modifiedData);
    static cv::Mat calcICPMatching(cv::Mat baseData, cv::Mat modifiedData);
    static ofMatrix4x4 cvMat2ofMat(cv::Mat cvMat);
    static cv::Mat ofMat2cvMat(ofMatrix4x4 ofMat);
    
private:
    vector<ofVec3d> basePointList;
    vector<ofVec3d> modifiedPointList;
    cv::Mat baseData;
    cv::Mat modifiedData;
};

#endif /* icp_hpp */
