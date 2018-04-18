#include "ofApp.h"

static void featureDetection(ofPixels& src, ofPixels* dst)
{
    cv::Mat srcMat = toCv(src);
    cv::Mat dstMat = toCv(*dst);
    
    cv::Mat descriptors;
    vector<cv::KeyPoint> keyPoints;
    
    cv::Ptr<cv::AKAZE> detector = cv::AKAZE::create();
    
    detector->detectAndCompute(srcMat, cv::noArray(), keyPoints, descriptors);
    cv::drawKeypoints(srcMat, keyPoints, dstMat, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
}

/**
 *  Test pencil sketch (OpenCV3)
 */

static void pencilSketch(ofPixels& src, ofPixels* dst)
{
    cv::Mat srcMat = toCv(src);
    cv::Mat dstMat = toCv(*dst);
    cv::Mat dst8UC1;
    
    cv::pencilSketch(srcMat, dst8UC1, dstMat, 60, 0.07f, 0.02f);
}

/**
 *  Test stylization (OpenCV3)
 */
static void stylization(ofPixels& src, ofPixels* dst)
{
    cv::Mat srcMat = toCv(src);
    cv::Mat dstMat = toCv(*dst);
    
    cv::stylization(srcMat, dstMat, 60, 0.45f);
}


//--------------------------------------------------------------
//
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(512*2, 512);
    
    mLenaImg.load("Lena.png");
    mResImg.allocate(mLenaImg.getWidth(), mLenaImg.getHeight(), mLenaImg.getImageType());
    
    featureDetection(mLenaImg.getPixels(), &mResImg.getPixels());
    mResImg.update();
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    mLenaImg.draw(0, 0);
    mResImg.draw(512, 0);
    
    ofDrawBitmapString("Push the number key (1, 2, 3)", 20, 20);
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key)
    {
        case '1':
        featureDetection(mLenaImg.getPixels(), &mResImg.getPixels());
        mResImg.update();
        break;
        
        case '2':
        pencilSketch(mLenaImg.getPixels(), &mResImg.getPixels());
        mResImg.update();
        break;
        
        case '3':
        stylization(mLenaImg.getPixels(), &mResImg.getPixels());
        mResImg.update();
        break;
    }
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
