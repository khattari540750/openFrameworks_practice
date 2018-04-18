#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // 1. get calibration 3D point & laser 2D point
    vector<ofVec3f> calibrationPoints;
    vector<ofVec2f> laserPoints;
    
    // 2. convert to cv format
    vector<cv::Point3f> objectPoints;
    for(int i=0; i<calibrationPoints.size(); i++) {
        cv::Point3f point3d;
        point3d.x = calibrationPoints[i].x;
        point3d.y = calibrationPoints[i].y;
        point3d.z = calibrationPoints[i].z;
        objectPoints.push_back(point3d);
    }
    
    vector<cv::Point2f> imagePoints;
     for(int i=0; i<imagePoints.size(); i++) {
         cv::Point2f point2d;
         point2d.x = laserPoints[i].x;
         point2d.y = laserPoints[i].y;
         imagePoints.push_back(point2d);
     }
    
    // 3.
    cv::Mat intrinsic; // internal parameter matrix
    cv::Mat distcoeffs; // distortion parameter
    cv::Mat rvec; // rotation vector
    cv::Mat tvec; // translation vector
    cv::solvePnPRansac(objectPoints, imagePoints, intrinsic, distcoeffs, rvec, tvec, true);
    
    // 4.
    cv::Mat rmat; // rotation matrix
    cv::Rodrigues(rvec, rmat); // use rodrigues of offical
    
    cv::Mat extrinsic;
    extrinsic = cv::Mat::eye(4,4,CV_32F);
    extrinsic.at<float>(0,0) = rmat.at<double>(0,0);
    extrinsic.at<float>(0,1) = rmat.at<double>(0,1);
    extrinsic.at<float>(0,2) = rmat.at<double>(0,2);
    extrinsic.at<float>(1,0) = rmat.at<double>(1,0);
    extrinsic.at<float>(1,1) = rmat.at<double>(1,1);
    extrinsic.at<float>(1,2) = rmat.at<double>(1,2);
    extrinsic.at<float>(2,0) = rmat.at<double>(2,0);
    extrinsic.at<float>(2,1) = rmat.at<double>(2,1);
    extrinsic.at<float>(2,2) = rmat.at<double>(2,2);
    extrinsic.at<float>(0,3) = rmat.at<double>(0);
    extrinsic.at<float>(1,3) = rmat.at<double>(1);
    extrinsic.at<float>(2,3) = rmat.at<double>(2);
    
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
