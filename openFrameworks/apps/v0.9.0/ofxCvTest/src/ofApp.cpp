#include "ofApp.h"



using namespace ofxCv;
using namespace cv;



void ofApp::setup()
{
    double posX = 1;
    double posY = 1;
    double posZ = 1;
    double rotX = 0.;
    double rotY = 0.;
    double rotZ = 0.;
    
    cv::Mat r_x = (cv::Mat_<double>(4,4) << 1,         0,          0, 0,
                                            0, cos(rotX), -sin(rotX), 0,
                                            0, sin(rotX),  cos(rotX), 0,
                                            0,         0,          0, 1);
    std::cout << "r_x=" << r_x << std::endl << std::endl;
    
    cv::Mat r_y = (cv::Mat_<double>(4,4) <<  cos(rotY), 0, sin(rotY), 0,
                                                     0, 1,         0, 0,
                                            -sin(rotY), 0, cos(rotY), 0,
                                                     0, 0,         0, 1);
    std::cout << "r_y=" << r_y << std::endl << std::endl;
    
    cv::Mat r_z = (cv::Mat_<double>(4,4) << cos(rotZ), -sin(rotZ), 0, 0,
                                            sin(rotZ),  cos(rotZ), 0, 0,
                                                    0,          0, 1, 0,
                                                    0,          0, 0, 1);
    std::cout << "r_z=" << r_z << std::endl << std::endl;
    
    cv::Mat r_pos = r_z*r_y*r_x;
    std::cout << "r_pos=" << r_pos << std::endl << std::endl;
    
    
    
    double pan = 0;
    double tilt = 0;
    double l0 = 0;
    double l1 = 0;
    double l2 = 0;
    
    cv::Mat r_p = (cv::Mat_<double>(4,4) << cos(pan), -sin(pan), 0,     0,
                                            sin(pan),  cos(pan), 0,     0,
                                                   0,         0, 1, l0+l1,
                                                   0,         0, 0,     1);
    std::cout << "r_p=" << r_p << std::endl << std::endl;
    
    cv::Mat r_t = (cv::Mat_<double>(4,4) <<  cos(tilt), 0, sin(tilt), l2,
                                                     0, 1,         0,  0,
                                            -sin(tilt), 0, cos(tilt),  0,
                                                     0, 0,         0,  1);
    std::cout << "r_t=" << r_t << std::endl << std::endl;
    
    cv::Mat r_moving = r_t*r_p;
    std::cout << "r_moving=" << r_moving << std::endl << std::endl;
    
    
    cv::Mat r = r_moving*r_pos;
    std::cout << "r=" << r << std::endl << std::endl;
    
    
    
    double f_x = 1;
    double f_y = 1;
    double c_x = 0;
    double c_y = 0;
    
    cv::Mat a = (cv::Mat_<double>(4,4) << f_x,   0, c_x, 0,
                                            0, f_y, c_y, 0,
                                            0,   0,   1, 0,
                                            0,   0,   0, 1,
                                            0,   0,   0, 1);
    
    cv::Mat c = a*r;
    
}


void ofApp::update()
{
    
}


void ofApp::draw()
{
    
}













/*
 #include "ofApp.h"
 
 
 
 using namespace ofxCv;
 using namespace cv;
 
 
 
 void ofApp::setup()
 {
 ofSetVerticalSync(true);
 
 kalman.init(1e-4, 1e-1); // invert of (smoothness, rapidness)
 
 line.setMode(OF_PRIMITIVE_LINE_STRIP);
 predicted.setMode(OF_PRIMITIVE_LINE_STRIP);
 estimated.setMode(OF_PRIMITIVE_LINE_STRIP);
 
 speed = 0.f;
 }
 
 
 void ofApp::update()
 {
 ofVec2f curPoint(mouseX, mouseY);
 line.addVertex(curPoint);
 
 kalman.update(curPoint); // feed measurement
 
 point = kalman.getPrediction(); // prediction before measurement
 predicted.addVertex(point);
 estimated.addVertex(kalman.getEstimation()); // corrected estimation after measurement
 
 speed = kalman.getVelocity().length();
 int alpha = ofMap(speed, 0, 20, 50, 255, true);
 line.addColor(ofColor(255, 255, 255, alpha));
 predicted.addColor(ofColor(255, 0, 0, alpha));
    estimated.addColor(ofColor(0, 255, 0, alpha));
}


void ofApp::draw()
{
    ofBackground(0);
    
    line.draw();
    
    predicted.draw();
    ofPushStyle();
    ofSetColor(ofColor::red, 128);
    ofFill();
    ofDrawCircle(point, speed * 2);
    ofPopStyle();
    
    estimated.draw();
}
*/















/*
#include "ofApp.h"



using namespace ofxCv;
using namespace cv;



void ofApp::setup()
{
    distorted.load("distorted.jpg");
    undistortedReference.load("undistorted.jpg");
    
    float imageWidth = 5616; // ImageWidth, pixels
    float imageHeight = 3744; // ImageLength, pixels
    float focalLength = 28; // FocalLength, mm
    float cropFactor = 0.975939; // SensorFormatFactor, "focal length multiplier", "crop factor"
    float focalLengthX = 0.778962; // FocalLengthX
    float focalLengthY = 0.778962; // FocalLengthY
    float principalPointX = 0.500000; // ImageXCenter, ratio
    float principalPointY = 0.500000; // ImageYCenter, ratio
    
    float k1 = -0.147131; // RadialDistortParam1
    float k2 = 0.084927; // RadialDistortParam2
    calibration.setDistortionCoefficients(k1, k2, 0, 0);
    
    Intrinsics intrinsics;
    cv::Point2d sensorSize(35 * cropFactor, 35 * cropFactor * imageHeight / imageWidth);
    cv::Size imageSize(distorted.getWidth(), distorted.getHeight());
    intrinsics.setup(focalLength, imageSize, sensorSize);
    calibration.setFillFrame(false);
    calibration.setIntrinsics(intrinsics);
    
    imitate(undistorted, distorted);
    
    Mat distortedMat = toCv(distorted);
    Mat undistortedMat = toCv(undistorted);
    calibration.undistort(distortedMat, undistortedMat);
    undistorted.update();
}


void ofApp::update()
{
}


void ofApp::draw()
{
    float scale = ofGetHeight() / distorted.getHeight();
    ofScale(scale, scale);
    distorted.draw(0, 0);
    if(ofGetKeyPressed('r')) {
        undistortedReference.draw(0, 0);
    }
    if(ofGetKeyPressed('u')) {
        undistorted.draw(0, 0);
    }
}
*/