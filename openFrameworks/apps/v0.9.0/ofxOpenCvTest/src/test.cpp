#include "test.h"




cv::Mat motionEstimationSVD(cv::Mat data1, cv::Mat data2)
{
    cv::Mat mm, ms;
    cv::reduce(data1, mm, 1, CV_REDUCE_AVG);
    cv::reduce(data2, ms, 1, CV_REDUCE_AVG);
    //std::cout << "data1 AVG=" << mm << std::endl;
    //std::cout << "data2 AVG=" << ms << std::endl;
    
    
    cv::Mat Mm(1, data1.cols, CV_64FC1, cv::Scalar(mm.at<double>(0,0)));
    Mm.resize(2, cv::Scalar(mm.at<double>(1,0)));
    Mm.resize(3,cv::Scalar(0));
    //std::cout << "Mm=" << Mm << std::endl;
    cv::Mat Ms(1, data2.cols, CV_64FC1, cv::Scalar(ms.at<double>(0,0)));
    Ms.resize(2, cv::Scalar(ms.at<double>(1,0)));
    Ms.resize(3,cv::Scalar(0));
    //std::cout << "Ms=" << Ms << std::endl;
    
    
    cv::Mat Mshifted = data1 - Mm;   //mm.at<double>(0,0)*data1;
    Mshifted.resize(2);
    cv::Mat Sshifted = data2 - Ms; //ms.at<double>(1,0)*data2;
    Sshifted.resize(2);
    //std::cout << "Mshifted=" << Mshifted << std::endl;
    //std::cout << "Sshifted=" << Sshifted << std::endl;
    
    
    cv::Mat A = Sshifted*Mshifted.t();
    //std::cout << "A=" << A << std::endl << std::endl;;
    
    
    cv::Mat w, u, vt;
    cv::SVD::compute(A, w, u, vt, cv::SVD::FULL_UV);
    //std::cout << "w=" << w << std::endl;
    //std::cout << "u=" << u << std::endl;
    //std::cout << "vt=" << vt << std::endl << std::endl;
    
    
    cv::Mat R = u*vt;
    R = R.t();
    mm.resize(2);
    ms.resize(2);
    cv::Mat t = mm - R*ms;
    //std::cout << "R=" << R << std::endl;
    //std::cout << "t=" << t << std::endl;
    
    
    cv::Mat Rt = cv::Mat::zeros(3,3,CV_64FC1);
    for(int i=0; i<R.rows; i++){
        for(int j=0; j<R.cols; j++){
            Rt.at<double>(i,j) = R.at<double>(i,j);
        }
    }
    for(int k=0; k<R.rows; k++){
        Rt.at<double>(k,Rt.cols-1) = t.at<double>(k,0);
    }
    Rt.at<double>(Rt.rows-1, Rt.cols-1) = 1;
    //std::cout << "Rt=" << Rt << std::endl;
    
    
    return Rt;
}



double findNearestPoint(cv::Mat data1, cv::Mat data2)
{
    double errorSum=0;
    
    for(int i=0; i<data1.cols; i++){
        double dx = data2.at<double>(0,i) - data1.at<double>(0,i);
        double dy = data2.at<double>(1,i) - data1.at<double>(1,i);
        double dist = sqrt(dx*dx + dy*dy);
        errorSum += dist;
    }
    
    return errorSum;
}



cv::Mat calcICPMatching(cv::Mat data1, cv::Mat data2)
{
    double preError=0;
    double dError=1000;
    double EPS=0.0001;
    int maxIter=1000;
    int count=0;
    
    cv::Mat Rt = cv::Mat::eye(3,3,CV_64FC1);
    cv::Mat NewData2 = data2.clone();
    
    while(dError > EPS) {
        
        count++;
        
        double error = findNearestPoint(data1, NewData2);
        cv::Mat Rt1 = motionEstimationSVD(data1, NewData2);
        
        NewData2 = Rt1*NewData2;
        Rt = Rt1*Rt;
        
        dError=abs(preError-error);
        std::cout << dError << std::endl;
        preError=error;
        
        // not convergence
        if(count > maxIter){
            std::cout << "count : Max Iteration" << std::endl;
            break;
        }
    }
    
    std::cout << "count : " << count << std::endl;
    
    return Rt;
}



double toRadian(double degree)
{
    return degree/180.0*pi;
}



cv::Mat Data1, Data2, Data3;
cv::Mat Gmm, Gms;
double true_shiftX;
double true_shiftY;
double true_rot;
double est_shiftX;
double est_shiftY;
double est_rot;



void testApp::setup()
{
    // of setting
    //ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
    
    
    // set variables
    int _nPoint=100;
    int _fieldLength=6;
    double _shiftX = 0.5;
    double _shiftY = 0.0;
    double _rot = 10;
    double _transitionSigma = 0.01;
    double _thetaSigma=1.0;
    
    
    // set data1 random
    cv::Mat data1(2,_nPoint,CV_64FC1);
    cv::RNG gen(cv::getTickCount());
    gen.fill(data1, cv::RNG::UNIFORM, cv::Scalar(-_fieldLength/2), cv::Scalar(_fieldLength/2));
    data1.resize(3, cv::Scalar(1));
    //std::cout << "data1=" << data1 << std::endl;
    //std::cout << "data1 rows=" << data1.rows << std::endl;
    //std::cout << "data1 cols=" << data1.cols << std::endl;
    
    
    // set data2 convert to data1
    double theta = toRadian(_rot) + toRadian(_thetaSigma)*gen.uniform(0.0, 1.0);
    cv::Mat Rot = (cv::Mat_<double>(3,3) << cos(theta), -sin(theta), 0,
                                            sin(theta),  cos(theta), 0,
                                                     0,           0, 1);
    cv::Mat Shift = (cv::Mat_<double>(3,3) << 1, 0, _shiftX,
                                              0, 1, _shiftY,
                                              0, 0,       1);
    cv::Mat noise(2,_nPoint,CV_64FC1);
    gen.fill(noise, cv::RNG::NORMAL, cv::Scalar(0), cv::Scalar(_transitionSigma));
    noise.resize(3, cv::Scalar(0));
    //std::cout << "noise=" << noise << std::endl;
    
    cv::Mat data2 = Shift*data1;
    data2 = data2+noise;
    data2 = Rot*data2;
    //std::cout << "data2=" << data2 << std::endl;
    
    
    
    
    // calc ICP
    cv::Mat Rt = calcICPMatching(data1, data2);
    std::cout << "Rt=" << Rt << std::endl;
    
    
    
    
    // after ICP
    cv::Mat data3 = Rt*data2;
    
    
    
    
    // print
    Data1 = data1;
    Data2 = data2;
    Data3 = data3;
    true_shiftX = _shiftX;
    true_shiftY = _shiftY;
    true_rot = _rot;
    est_shiftX = Rt.at<double>(0,2);
    est_shiftY = Rt.at<double>(1,2);
    est_rot = acos(Rt.at<double>(1,1))/pi*180;
    
    
    //
    data3Flag = false;
}


void testApp::update()
{
    
}


void testApp::draw()
{
    ofSetColor(ofColor::blue);
    ofFill();
    for(int i=0; i<Data1.cols; i++){
        double x1 = Data1.at<double>(0,i)* ofGetWidth()/15 + ofGetWidth()/2;
        double y1 = -Data1.at<double>(1,i)* ofGetWidth()/15 + ofGetHeight()/2;
        ofDrawCircle( x1, y1, 3 );
    }
    
    if(!data3Flag){
        ofSetColor(ofColor::red);
        ofFill();
        for(int i=0; i<Data2.cols; i++){
            double x2 = Data2.at<double>(0,i)* ofGetWidth()/15 + ofGetWidth()/2;
            double y2 = -Data2.at<double>(1,i)* ofGetWidth()/15 + ofGetHeight()/2;
            ofDrawCircle( x2, y2, 3);
        }
    }
    
    if(data3Flag){
        ofSetColor(ofColor::red);
        ofFill();
        for(int i=0; i<Data3.cols; i++){
            double x3 = Data3.at<double>(0,i)* ofGetWidth()/15 + ofGetWidth()/2;
            double y3 = -Data3.at<double>(1,i)* ofGetWidth()/15 + ofGetHeight()/2;
            ofDrawCircle( x3, y3, 3);
        }
    }
    
    
    ofSetColor(0);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofPoint(10,20));
    
    
    
    ofSetColor(0,0,255);
    ofDrawBitmapString("convergence       : ", ofPoint(10,ofGetHeight()-20*9));
    ofDrawBitmapString("true x[m]         : " + ofToString(true_shiftX),ofPoint(10,ofGetHeight()-20*8));
    ofDrawBitmapString("true y[m]         : " + ofToString(true_shiftY),ofPoint(10,ofGetHeight()-20*7));
    ofDrawBitmapString("true rot[deg]     : " + ofToString(true_rot), ofPoint(10,ofGetHeight()-20*6));
    ofDrawBitmapString("estimated x[m]    : " + ofToString(est_shiftX), ofPoint(10,ofGetHeight()-20*5));
    ofDrawBitmapString("estimated y[m]    : " + ofToString(est_shiftY), ofPoint(10,ofGetHeight()-20*4));
    ofDrawBitmapString("estimated rot[deg]: " + ofToString(est_rot), ofPoint(10,ofGetHeight()-20*3));
    ofDrawBitmapString("target Position Y : ", ofPoint(10,ofGetHeight()-20*2));
    ofDrawBitmapString("target Position Z : ", ofPoint(10,ofGetHeight()-20*1));
}


void testApp::keyPressed  (int key)
{
    if(!data3Flag) data3Flag = true;
    else data3Flag = false;
}


void testApp::keyReleased(int key)
{
}


void testApp::mouseMoved(int x, int y)
{
}


void testApp::mouseDragged(int x, int y, int button)
{
}


void testApp::mousePressed(int x, int y, int button)
{
}


void testApp::mouseReleased(int x, int y, int button)
{
}


void testApp::windowResized(int w, int h)
{
}







movingLight::movingLight()
{
    l0 = 200;
    l1 = 200;
    l2 = 100;
}



movingLight::~movingLight()
{
    
}


double movingLight::inverseKineticsPan(double x, double y)
{
    return atan2(y, x);
}


double movingLight::inverseKineticsTilt(double x, double y, double z)
{
    return atan2( (z-l1-l0), sqrt(x*x+y*y) );
}


double movingLight::inverseKineticsOpticalAxis(double x, double y, double z)
{
    return (z-l0-l1)/(inverseKineticsTilt(x, y, z)) -l2;
}


