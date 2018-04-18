#include "ICP3DTest.h"



//--------------------------------------------------------------
void ICP3DTest::setup()
{
    // of setting
    //ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
    
    // set variables
    int _nPoint=3;
    int _fieldLength=6; //6;
    double _shiftX = 1.5;
    double _shiftY = 0.0;
    double _shiftZ = 0.3;
    double _rotX = 10;//10; //[deg]
    double _rotY = 20;//5; //[deg]
    double _rotZ = 30;//1; //[deg]
    double _transitionSigma = 0.01;
    double _thetaSigma=1.0;
    
    // set data1 random
    cv::Mat data1(3,_nPoint,CV_64FC1);
    cv::RNG gen(cv::getTickCount());
    gen.fill(data1, cv::RNG::UNIFORM, cv::Scalar(-_fieldLength/2), cv::Scalar(_fieldLength/2));
    data1.resize(4, cv::Scalar(1));
    
    // set data2 convert to data1
    double thetaX = toRadian(_rotX) + toRadian(_thetaSigma)*gen.uniform(0.0, 1.0);
    cv::Mat RotX = (cv::Mat_<double>(4,4) << 1,           0,            0, 0,
                                             0, cos(thetaX), -sin(thetaX), 0,
                                             0, sin(thetaX),  cos(thetaX), 0,
                                             0,           0,            0, 1);
    double thetaY = toRadian(_rotY) + toRadian(_thetaSigma)*gen.uniform(0.0, 1.0);
    cv::Mat RotY = (cv::Mat_<double>(4,4) <<  cos(thetaY), 0, sin(thetaY), 0,
                                                        0, 1,           0, 0,
                                             -sin(thetaY), 0, cos(thetaY), 0,
                                                        0, 0,           0, 1);
    double thetaZ = toRadian(_rotZ) + toRadian(_thetaSigma)*gen.uniform(0.0, 1.0);
    cv::Mat RotZ = (cv::Mat_<double>(4,4) << cos(thetaZ), -sin(thetaZ), 0, 0,
                                             sin(thetaZ),  cos(thetaZ), 0, 0,
                                                       0,            0, 1, 0,
                                                       0,            0, 0, 1);

    cv::Mat Rot = RotX*RotY*RotZ;
    
    cv::Mat Shift = (cv::Mat_<double>(4,4) << 1, 0, 0, _shiftX,
                                              0, 1, 0, _shiftY,
                                              0, 0, 1, _shiftZ,
                                              0, 0, 0,       1);
    
    cv::Mat noise(3,_nPoint,CV_64FC1);
    gen.fill(noise, cv::RNG::NORMAL, cv::Scalar(0), cv::Scalar(_transitionSigma));
    noise.resize(4, cv::Scalar(0));
    cv::Mat data2 = Shift*data1;
    data2 = data2+noise;
    data2 = Rot*data2;
    
    
    // calc ICP
    cv::Mat Rt = calcICPMatching(data1, data2);
    std::cout << "Rt=" << Rt << std::endl;
    
    // after ICP
    _drawBaseData = data1;
    _drawMeasurementData = data2;
    _drawFixData = Rt*data2;
    
     
     
    //gui setting
    _fixFlag = false;
    _cam = new ofEasyCam();
    _cam->setDistance(800);
    for(int i=0; i<_drawBaseData.cols; i++){
        ofSpherePrimitive o;
        o.set(3, 3);
        _baseDataObj.push_back(o);
    }
    
    for(int i=0; i<_drawMeasurementData.cols; i++){
        ofSpherePrimitive o;
        o.set(3, 3);
        _measurementDataObj.push_back(o);
    }
    
    for(int i=0; i<_drawFixData.cols; i++){
        ofSpherePrimitive o;
        o.set(3, 3);
        _fixDataObj.push_back(o);
    }
}


//--------------------------------------------------------------
void ICP3DTest::update()
{
}


//--------------------------------------------------------------
void ICP3DTest::draw()
{
    _cam->begin();
    
    ofSetColor(ofColor::blue);
    ofFill();
    for(int i=0; i<_drawBaseData.cols; i++){
        double x1 = _drawBaseData.at<double>(0,i)* ofGetWidth()/10;// + ofGetWidth()/2;
        double y1 = -_drawBaseData.at<double>(1,i)* ofGetWidth()/10;// + ofGetHeight()/2;
        double z1 = -_drawBaseData.at<double>(2,i)* ofGetWidth()/10;
        _baseDataObj[i].setPosition(x1, y1, z1);
        _baseDataObj[i].draw();
    }
    
    if(!_fixFlag){
        ofSetColor(ofColor::red);
        ofFill();
        for(int i=0; i<_drawMeasurementData.cols; i++){
            double x2 = _drawMeasurementData.at<double>(0,i)* ofGetWidth()/10;// + ofGetWidth()/2;
            double y2 = -_drawMeasurementData.at<double>(1,i)* ofGetWidth()/10;// + ofGetHeight()/2;
            double z2 = -_drawMeasurementData.at<double>(2,i)* ofGetWidth()/10;
            _measurementDataObj[i].setPosition(x2, y2, z2);
            _measurementDataObj[i].draw();
        }
    }
    
    if(_fixFlag){
        ofSetColor(ofColor::red);
        ofFill();
        for(int i=0; i<_drawFixData.cols; i++){
            double x3 = _drawFixData.at<double>(0,i)* ofGetWidth()/10;// + ofGetWidth()/2;
            double y3 = -_drawFixData.at<double>(1,i)* ofGetWidth()/10;// + ofGetHeight()/2;
            double z3 = -_drawFixData.at<double>(2,i)* ofGetWidth()/10;
            _fixDataObj[i].setPosition(x3, y3, z3);
            _fixDataObj[i].draw();
        }
    }
    
    _cam->end();
    
    ofSetColor(0);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofPoint(10,20));
}











//--------------------------------------------------------------
double ICP3DTest::toRadian(double degree)
{
    return degree/180.0*pi;
}


//--------------------------------------------------------------
cv::Mat ICP3DTest::motionEstimationSVD(cv::Mat baseData, cv::Mat fixData)
{
    cv::Mat mm, ms;
    cv::reduce(baseData, mm, 1, CV_REDUCE_AVG);
    cv::reduce(fixData, ms, 1, CV_REDUCE_AVG);
    
    cv::Mat Mm(1, baseData.cols, CV_64FC1, cv::Scalar(mm.at<double>(0,0)));
    Mm.resize(2, cv::Scalar(mm.at<double>(1,0)));
    Mm.resize(3, cv::Scalar(mm.at<double>(2,0)));
    Mm.resize(4,cv::Scalar(0));
    cv::Mat Ms(1, fixData.cols, CV_64FC1, cv::Scalar(ms.at<double>(0,0)));
    Ms.resize(2, cv::Scalar(ms.at<double>(1,0)));
    Ms.resize(3, cv::Scalar(ms.at<double>(2,0)));
    Ms.resize(4,cv::Scalar(0));
    
    cv::Mat Mshifted = baseData - Mm;
    Mshifted.resize(3);
    cv::Mat Sshifted = fixData - Ms;
    Sshifted.resize(3);
    
    cv::Mat A = Sshifted*Mshifted.t();
    cv::Mat w, u, vt;
    cv::SVD::compute(A, w, u, vt, cv::SVD::FULL_UV);
    
    cv::Mat R = u*vt;
    R = R.t();
    mm.resize(3);
    ms.resize(3);
    cv::Mat t = mm - R*ms;
    
    cv::Mat Rt = cv::Mat::zeros(4,4,CV_64FC1);
    for(int i=0; i<R.rows; i++){
        for(int j=0; j<R.cols; j++){
            Rt.at<double>(i,j) = R.at<double>(i,j);
        }
    }
    for(int k=0; k<R.rows; k++){
        Rt.at<double>(k,Rt.cols-1) = t.at<double>(k,0);
    }
    Rt.at<double>(Rt.rows-1, Rt.cols-1) = 1;
    
    return Rt;

}


//--------------------------------------------------------------
double ICP3DTest::findNearestPoint(cv::Mat baseData, cv::Mat fixData)
{
    double errorSum=0;
    
    for(int i=0; i<baseData.cols; i++){
        double dx = fixData.at<double>(0,i) - baseData.at<double>(0,i);
        double dy = fixData.at<double>(1,i) - baseData.at<double>(1,i);
        double dz = fixData.at<double>(2,i) - baseData.at<double>(2,i);
        double dist = sqrt(dx*dx + dy*dy + dz*dz);
        errorSum += dist;
    }
    
    return errorSum;
}


//--------------------------------------------------------------
cv::Mat ICP3DTest::calcICPMatching(cv::Mat baseData, cv::Mat fixData)
{
    double preError=0;
    double dError=1000;
    double EPS=0.0001;
    int maxIter=1000;
    int count=0;
    
    cv::Mat NewFixData = fixData.clone();
    cv::Mat Rt = cv::Mat::eye(4,4,CV_64FC1);
    
    while(dError > EPS) {
        count++;
        double error = findNearestPoint(baseData, NewFixData);
        cv::Mat Rt1 = motionEstimationSVD(baseData, NewFixData);
        
        NewFixData = Rt1*NewFixData;
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








//--------------------------------------------------------------
void ICP3DTest::keyPressed(int key)
{
    if(!_fixFlag) _fixFlag = true;
    else _fixFlag = false;
}


//--------------------------------------------------------------
void ICP3DTest::keyReleased(int key){}

//--------------------------------------------------------------
void ICP3DTest::mouseMoved(int x, int y ){}

//--------------------------------------------------------------
void ICP3DTest::mouseDragged(int x, int y, int button){}

//--------------------------------------------------------------
void ICP3DTest::mousePressed(int x, int y, int button){}

//--------------------------------------------------------------
void ICP3DTest::mouseReleased(int x, int y, int button){}

//--------------------------------------------------------------
void ICP3DTest::mouseEntered(int x, int y){}

//--------------------------------------------------------------
void ICP3DTest::mouseExited(int x, int y){}

//--------------------------------------------------------------
void ICP3DTest::windowResized(int w, int h){}

//--------------------------------------------------------------
void ICP3DTest::gotMessage(ofMessage msg){}

//--------------------------------------------------------------
void ICP3DTest::dragEvent(ofDragInfo dragInfo){}
