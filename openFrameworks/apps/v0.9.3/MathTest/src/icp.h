//!
//! @file icp.hpp
//! @brief icp (please use well-known corresponding point)
//! @author HATTORI Kohei
//! @date 4/7/2016
//!

#ifndef ICP_HPP
#define ICP_HPP

#include "ofHatVectorMath.h"
#include "ofMain.h"
#include "ofxOpenCv.h"

class ICP {

public:
  ofHatMatrix4x4 calcICP();
  void setPoint(ofHatVec3d basePoint, ofHatVec3d modifiedPoint);

private:
  cv::Mat motionEstimationSVD(cv::Mat baseData, cv::Mat modifiedData);
  double findNearestPoint(cv::Mat baseData, cv::Mat modifiedData);
  cv::Mat calcICPMatching(cv::Mat baseData, cv::Mat modifiedData);
  ofHatMatrix4x4 cvMat2ofMat(cv::Mat cvMat);
  cv::Mat ofMat2cvMat(ofHatMatrix4x4 ofMat);

private:
  vector<ofHatVec3d> basePointsList;
  vector<ofHatVec3d> modifiedPointsList;
  cv::Mat baseData;
  cv::Mat modifiedData;
};

#endif