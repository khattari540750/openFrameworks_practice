//!
//! @file icp.hpp
//! @brief icp (please use well-known corresponding point)
//! @author HATTORI Kohei
//! @date 4/7/2016
//!

#ifndef ICP_HPP
#define ICP_HPP

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
  cv::Mat motionEstimationSVD(cv::Mat baseData, cv::Mat modifiedData);
  double findNearestPoint(cv::Mat baseData, cv::Mat modifiedData);
  cv::Mat calcICPMatching(cv::Mat baseData, cv::Mat modifiedData);
  ofMatrix4x4 cvMat2ofMat(cv::Mat cvMat);
  cv::Mat ofMat2cvMat(ofMatrix4x4 ofMat);

private:
  vector<ofVec3d> basePointsList;
  vector<ofVec3d> modifiedPointsList;
  cv::Mat baseData;
  cv::Mat modifiedData;
};

#endif // ICP_HPP
