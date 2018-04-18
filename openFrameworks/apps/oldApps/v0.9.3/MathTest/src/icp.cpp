//!
//! @file icp.cpp
//! @brief icp (please use well-known corresponding point)
//! @author HATTORI Kohei
//! @date 4/7/2016
//!

#include "icp.h"

//==============================================================================
// public functions
//==============================================================================
//!
//! @fn
//! @brief ICP::calcICP
//! @return rotation matrix
//!
ofHatMatrix4x4 ICP::calcICP() {
  cv::Mat data1(4, basePointsList.size(), CV_64FC1);
  cv::Mat data2(4, modifiedPointsList.size(), CV_64FC1);

  for (int i = 0; i < basePointsList.size(); i++) {
    data1.at<double>(0, i) = basePointsList[i].x;
    data1.at<double>(1, i) = basePointsList[i].y;
    data1.at<double>(2, i) = basePointsList[i].z;
    data1.at<double>(3, i) = 1.;
  }
  basePointsList.clear();

  for (int i = 0; i < modifiedPointsList.size(); i++) {
    data2.at<double>(0, i) = modifiedPointsList[i].x;
    data2.at<double>(1, i) = modifiedPointsList[i].y;
    data2.at<double>(2, i) = modifiedPointsList[i].z;
    data2.at<double>(3, i) = 1.;
  }
  modifiedPointsList.clear();

  cv::Mat Rt = calcICPMatching(data1, data2);
  // cout << "Rt" << endl;
  // cout << Rt << endl;

  return cvMat2ofMat(Rt);
}

//------------------------------------------------------------------------------
//!
//! @fn
//! @brief ICP::setPoint
//! @param baseData
//! @param modifiedData
//!
void ICP::setPoint(ofHatVec3d basePoint, ofHatVec3d modifiedPoint) {
  basePointsList.push_back(basePoint);
  modifiedPointsList.push_back(modifiedPoint);
  //  cout << "set baseData x=" << vb.x << endl;
  //  cout << "set baseData y=" << vb.y << endl;
  //  cout << "set baseData z=" << vb.z << endl;
  //  cout << "set modifedData x=" << vm.x << endl;
  //  cout << "set modifedData y=" << vm.y << endl;
  //  cout << "set modifedData z=" << vm.z << endl;
}

//==============================================================================
// private functions
//==============================================================================
//!
//! @fn
//! @brief ICP::motionEstimationSVD
//! @param baseData
//! @param modifiedData
//! @return
//!
cv::Mat ICP::motionEstimationSVD(cv::Mat baseData, cv::Mat modifiedData) {
  cv::Mat mm, ms;
  cv::reduce(baseData, mm, 1, CV_REDUCE_AVG);
  cv::reduce(modifiedData, ms, 1, CV_REDUCE_AVG);

  cv::Mat Mm(1, baseData.cols, CV_64FC1, cv::Scalar(mm.at<double>(0, 0)));
  Mm.resize(2, cv::Scalar(mm.at<double>(1, 0)));
  Mm.resize(3, cv::Scalar(mm.at<double>(2, 0)));
  Mm.resize(4, cv::Scalar(0));
  cv::Mat Ms(1, modifiedData.cols, CV_64FC1, cv::Scalar(ms.at<double>(0, 0)));
  Ms.resize(2, cv::Scalar(ms.at<double>(1, 0)));
  Ms.resize(3, cv::Scalar(ms.at<double>(2, 0)));
  Ms.resize(4, cv::Scalar(0));

  cv::Mat Mshifted = baseData - Mm;
  Mshifted.resize(3);
  cv::Mat Sshifted = modifiedData - Ms;
  Sshifted.resize(3);

  cv::Mat A = Sshifted * Mshifted.t();
  cv::Mat w, u, vt;
  cv::SVD::compute(A, w, u, vt, cv::SVD::FULL_UV);

  cv::Mat R = u * vt;
  R = R.t();
  mm.resize(3);
  ms.resize(3);
  cv::Mat t = mm - R * ms;

  cv::Mat Rt = cv::Mat::zeros(4, 4, CV_64FC1);
  for (int i = 0; i < R.rows; i++) {
    for (int j = 0; j < R.cols; j++) {
      Rt.at<double>(i, j) = R.at<double>(i, j);
    }
  }
  for (int k = 0; k < R.rows; k++) {
    Rt.at<double>(k, Rt.cols - 1) = t.at<double>(k, 0);
  }
  Rt.at<double>(Rt.rows - 1, Rt.cols - 1) = 1;

  return Rt;
}

//------------------------------------------------------------------------------
//!
//! @fn
//! @brief ICP::findNearestPoint
//! @param baseData
//! @param modifiedData
//! @return
//!
double ICP::findNearestPoint(cv::Mat baseData, cv::Mat modifiedData) {
  double errorSum = 0;
  for (int i = 0; i < baseData.cols; i++) {
    double dx = modifiedData.at<double>(0, i) - baseData.at<double>(0, i);
    double dy = modifiedData.at<double>(1, i) - baseData.at<double>(1, i);
    double dz = modifiedData.at<double>(2, i) - baseData.at<double>(2, i);
    double dist = sqrt(dx * dx + dy * dy + dz * dz);
    errorSum += dist;
  }

  return errorSum;
}

//------------------------------------------------------------------------------
//!
//! @fn
//! @brief ICP::calcICPMatching
//! @param baseData
//! @param modifiedData
//! @return
//!
cv::Mat ICP::calcICPMatching(cv::Mat baseData, cv::Mat modifiedData) {
  double preError = 0;
  double dError = 1000;
  double EPS = 0.0001;
  int maxIter = 1000;
  int count = 0;

  cv::Mat NewmodifiedData = modifiedData.clone();
  cv::Mat Rt = cv::Mat::eye(4, 4, CV_64FC1);

  while (dError > EPS) {
    count++;
    double error = findNearestPoint(baseData, NewmodifiedData);
    // std::cout << "error:" << error << std::endl;
    cv::Mat Rt1 = motionEstimationSVD(baseData, NewmodifiedData);

    NewmodifiedData = Rt1 * NewmodifiedData;
    Rt = Rt1 * Rt;

    dError = abs(preError - error);
    // std::cout << "dError:" << dError << std::endl;
    preError = error;

    // not convergence
    if (count > maxIter) {
      // std::cout << "count : Max Iteration" << std::endl;
      break;
    }
  }

  // std::cout << "count : " << count << std::endl;
  return Rt;
}

//------------------------------------------------------------------------------
//!
//! @fn
//! @brief ICP::cvMat2ofMat
//! @param cvMat
//! @return
//!
ofHatMatrix4x4 ICP::cvMat2ofMat(cv::Mat cvMat) {
  ofHatMatrix4x4 ret;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ret._mat[i][j] = cvMat.at<double>(i, j);
    }
  }
  return ret;
}

//------------------------------------------------------------------------------
//!
//! @fn
//! @brief ICP::ofMat2cvMat
//! @param ofxMat
//! @return
//!
cv::Mat ICP::ofMat2cvMat(ofHatMatrix4x4 ofMat) {
  cv::Mat ret(4, 4, CV_64FC1);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ret.at<double>(i, j) = ofMat._mat[i][j];
    }
  }
  return ret;
}