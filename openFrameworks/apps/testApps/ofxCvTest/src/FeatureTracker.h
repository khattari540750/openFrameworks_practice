#ifndef FeatureTracker_h
#define FeatureTracker_h

#include "ofMain.h"
#include "ofxCv.h"

class FeatureTracker {
   public:
    float f;
    float sx, sy;
    float w, h;
    float fovy, aspect;

    cv::Mat intrinsic;
    cv::Mat distcoeffs;
    cv::Mat extrinsic;
};

#endif
