//
//  utils.h
//  openCV3Test
//
//  Created by 服部 弘平 on 2018/04/19.
//

#ifndef utils_h
#define utils_h

#include "ofMain.h"
#include <opencv2/core.hpp>

template <typename T>
static cv::Mat toCv(ofPixels_<T>& pix)
{
    int depth;
    switch(pix.getBytesPerChannel())
    {
        case 4: depth = CV_32F;
        case 2: depth = CV_16U;
        case 1: default: depth = CV_8U;
    }
    return cv::Mat(pix.getHeight(), pix.getWidth(), CV_MAKETYPE(depth, pix.getNumChannels()), pix.getData(), 0);
}

#endif /* utils_h */
