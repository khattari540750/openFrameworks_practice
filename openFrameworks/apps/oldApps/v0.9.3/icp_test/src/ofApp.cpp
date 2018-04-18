//!
//! @file ofApp.cpp
//! @brief 3D icp test
//! @author HATTORI Kohei
//! @date 4/7/2016
//!

#include "ofApp.h"

//--------------------------------------------------------------
//!
//! @fn
//! @brief ofApp::setup
//!
void ofApp::setup() {
  // of setting
  ofEnableAlphaBlending();
  ofSetFrameRate(60);

  // set experimental variables
  int nPoint = 4;
  int fieldLength = 200;          //[mm]
  double shiftX = 10;             //[mm]
  double shiftY = 20;             //[mm]
  double shiftZ = 25;             //[mm]
  double rotX = 5;                //[deg]
  double rotY = 2;                //[deg]
  double rotZ = 3;                //[deg]
  double transitionSigma = 3.000; //[mm]
  double thetaSigma = 2.0;        //[deg]

  // set data1 = random
  cv::Mat data1(3, nPoint, CV_64FC1);
  cv::RNG gen(cv::getTickCount());
  gen.fill(data1, cv::RNG::UNIFORM, cv::Scalar(-fieldLength / 2),
           cv::Scalar(fieldLength / 2));
  data1.resize(4, cv::Scalar(1));

  // set data2 = convert to data1
  double thetaX = toRadian(rotX) + toRadian(thetaSigma) * gen.uniform(0.0, 1.0);
  cv::Mat RotX = (cv::Mat_<double>(4, 4) << 1, 0, 0, 0, 0, cos(thetaX),
                  -sin(thetaX), 0, 0, sin(thetaX), cos(thetaX), 0, 0, 0, 0, 1);
  double thetaY = toRadian(rotY) + toRadian(thetaSigma) * gen.uniform(0.0, 1.0);
  cv::Mat RotY = (cv::Mat_<double>(4, 4) << cos(thetaY), 0, sin(thetaY), 0, 0,
                  1, 0, 0, -sin(thetaY), 0, cos(thetaY), 0, 0, 0, 0, 1);
  double thetaZ = toRadian(rotZ) + toRadian(thetaSigma) * gen.uniform(0.0, 1.0);
  cv::Mat RotZ = (cv::Mat_<double>(4, 4) << cos(thetaZ), -sin(thetaZ), 0, 0,
                  sin(thetaZ), cos(thetaZ), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
  cv::Mat Rot = RotX * RotY * RotZ;
  cv::Mat Shift = (cv::Mat_<double>(4, 4) << 1, 0, 0, shiftX, 0, 1, 0, shiftY,
                   0, 0, 1, shiftZ, 0, 0, 0, 1);
  cv::Mat noise(3, nPoint, CV_64FC1);
  gen.fill(noise, cv::RNG::NORMAL, cv::Scalar(0), cv::Scalar(transitionSigma));
  noise.resize(4, cv::Scalar(0));

  cv::Mat data2 = Shift * data1;
  data2 = data2 + noise;
  data2 = Rot * data2;

  // calc ICP
//  for (int i = 0; i < nPoint; i++) {
//    ofVec3f b, m;
//    b.x = (float)data1.at<double>(0, i);
//    b.y = (float)data1.at<double>(1, i);
//    b.z = (float)data1.at<double>(2, i);
//    m.x = (float)data2.at<double>(0, i);
//    m.y = (float)data2.at<double>(1, i);
//    m.z = (float)data2.at<double>(2, i);
//    icp.setPoint(b, m);
//  }

  ofVec3f b, m;

  data1.at<double>(0, 0) = 124.68;
  data1.at<double>(1, 0) = -0.657211;
  data1.at<double>(2, 0) = 358.911;
  data2.at<double>(0, 0) = 124.825;
  data2.at<double>(1, 0) = -2.0699;
  data2.at<double>(2, 0) = 356.272;
  b.x = (float)data1.at<double>(0, 0);
  b.y = (float)data1.at<double>(1, 0);
  b.z = (float)data1.at<double>(2, 0);
  m.x = (float)data2.at<double>(0, 0);
  m.y = (float)data2.at<double>(1, 0);
  m.z = (float)data2.at<double>(2, 0);
  icp.setPoint(b, m);

  data1.at<double>(0, 1) = 124.46;
  data1.at<double>(1, 1) = -7.45536;
  data1.at<double>(2, 1) = 358.894;
  data2.at<double>(0, 1) = 124.513;
  data2.at<double>(1, 1) = -9.0126;
  data2.at<double>(2, 1) = 356.35;
  b.x = (float)data1.at<double>(0, 1);
  b.y = (float)data1.at<double>(1, 1);
  b.z = (float)data1.at<double>(2, 1);
  m.x = (float)data2.at<double>(0, 1);
  m.y = (float)data2.at<double>(1, 1);
  m.z = (float)data2.at<double>(2, 1);
  icp.setPoint(b, m);

  data1.at<double>(0, 2) = 123.877;
  data1.at<double>(1, 2) = -14.1754;
  data1.at<double>(2, 2) = 358.859;
  data2.at<double>(0, 2) = 123.819;
  data2.at<double>(1, 2) = -15.9232;
  data2.at<double>(2, 2) = 356.342;
  b.x = (float)data1.at<double>(0, 2);
  b.y = (float)data1.at<double>(1, 2);
  b.z = (float)data1.at<double>(2, 2);
  m.x = (float)data2.at<double>(0, 2);
  m.y = (float)data2.at<double>(1, 2);
  m.z = (float)data2.at<double>(2, 2);
  icp.setPoint(b, m);

  data1.at<double>(0, 3) = 122.945;
  data1.at<double>(1, 3) = -20.7901;
  data1.at<double>(2, 3) = 358.798;
  data2.at<double>(0, 3) = 122.784;
  data2.at<double>(1, 3) = -22.5839;
  data2.at<double>(2, 3) = 356.246;
  b.x = (float)data1.at<double>(0, 3);
  b.y = (float)data1.at<double>(1, 3);
  b.z = (float)data1.at<double>(2, 3);
  m.x = (float)data2.at<double>(0, 3);
  m.y = (float)data2.at<double>(1, 3);
  m.z = (float)data2.at<double>(2, 3);
  icp.setPoint(b, m);

  ofMatrix4x4 ofRt = icp.calcICP();
  cv::Mat Rt = ofMat2cvMat(ofRt);

  //display data
  float posX = ofRt._mat[0][3];
  float posY = ofRt._mat[1][3];
  float posZ = ofRt._mat[2][3];
  ofQuaternion q = ofRt.getRotate();
  float angle, rotateX, rotateY, rotateZ;
  q.getRotate(angle, rotateX, rotateY, rotateZ);
  cout << "--------------------------------------" << endl;
  cout << "points:" << nPoint << endl;
  cout << "shift noise:" << transitionSigma << "[mm]" << endl;
  cout << "posX:" << posX << "[mm]" << "  diff:" << shiftX + posX << "[mm]" << endl;
  cout << "posY:" << posY << "[mm]" << "  diff:" << shiftY + posY << "[mm]" << endl;
  cout << "posZ:" << posZ << "[mm]" << "  diff:" << shiftZ + posZ << "[mm]" << endl;
  cout << "rotateX:" << rotateX*angle << endl;
  cout << "rotateY:" << rotateY*angle << endl;
  cout << "rotateZ:" << rotateZ*angle << endl;
  cout << "angle:" << angle << endl;
  cout << "Rt : " << endl;
  cout << Rt << endl;


  // after ICP
  drawBaseData = data1;
  drawMeasurementData = data2;
  drawFixData =  Rt * data2;

  // graphics setting
  fixFlag = false;
  cam.setDistance(fieldLength * 2);
  int sphereSize = fieldLength/100;
  if(sphereSize<1) sphereSize = 1;
  for (int i = 0; i < drawBaseData.cols; i++) {
    ofSpherePrimitive o;
    o.set(sphereSize, sphereSize);
    baseDataObjsList.push_back(o);
  }
  for (int i = 0; i < drawMeasurementData.cols; i++) {
    ofSpherePrimitive o;
    o.set(sphereSize, sphereSize);
    measurementDataObjsList.push_back(o);
  }
  for (int i = 0; i < drawFixData.cols; i++) {
    ofSpherePrimitive o;
    o.set(sphereSize, sphereSize);
    modifiedDataObjsList.push_back(o);
  }
}

//--------------------------------------------------------------
//!
//! @fn
//! @brief ofApp::update
//!
void ofApp::update() {}

//--------------------------------------------------------------
//!
//! @fn
//! @brief ofApp::draw
//!
void ofApp::draw() {
  cam.begin();

  ofSetColor(ofColor::blue);
  ofFill();

  // display basedata
  for (int i = 0; i < drawBaseData.cols; i++) {
    double x1 = drawBaseData.at<double>(0, i);
    double y1 = drawBaseData.at<double>(1, i);
    double z1 = drawBaseData.at<double>(2, i);
    baseDataObjsList[i].setPosition(x1, y1, z1);
    baseDataObjsList[i].draw();
  }

  // display
  if (!fixFlag) {
    ofSetColor(ofColor::red);
    ofFill();
    for (int i = 0; i < drawMeasurementData.cols; i++) {
      double x2 = drawMeasurementData.at<double>(0, i);
      double y2 = drawMeasurementData.at<double>(1, i);
      double z2 = drawMeasurementData.at<double>(2, i);
      measurementDataObjsList[i].setPosition(x2, y2, z2);
      measurementDataObjsList[i].draw();
    }
  }

  // display
  if (fixFlag) {
    ofSetColor(ofColor::red);
    ofFill();
    for (int i = 0; i < drawFixData.cols; i++) {
      double x3 = drawFixData.at<double>(0, i);
      double y3 = drawFixData.at<double>(1, i);
      double z3 = drawFixData.at<double>(2, i);
      modifiedDataObjsList[i].setPosition(x3, y3, z3);
      modifiedDataObjsList[i].draw();
    }
  }

  cam.end();

  ofSetColor(0);
  ofDrawBitmapString(ofToString(ofGetFrameRate()), ofPoint(10, 20));
}

//--------------------------------------------------------------
//!
//! @fn
//! @brief ofApp::keyPressed
//! @param key
//!
void ofApp::keyPressed(int key) {
  if (!fixFlag)
    fixFlag = true;
  else
    fixFlag = false;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}

//--------------------------------------------------------------
//!
//! @fn
//! @brief ofApp::toRadian
//! @param degree
//! @return
//!
double ofApp::toRadian(double degree) { return degree / 180.0 * pi; }

//--------------------------------------------------------------
//!
//! @fn
//! @brief ofApp::ofMat2cvMat
//! @param ofMat
//! @return
//!
cv::Mat ofApp::ofMat2cvMat(ofMatrix4x4 ofMat) {
  cv::Mat ret(4, 4, CV_64FC1);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ret.at<double>(i, j) = ofMat._mat[i][j];
    }
  }
  return ret;
}
