#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    int boud = 115200;
    string modem = "/dev/tty.usbmodem1411";
    serial.setup(modem, boud);
}

//--------------------------------------------------------------
void ofApp::update(){
    nBytesRead = 0;
    int nRead = 0;
    char bytesRead[3];
    unsigned char bytesReturned[3];
    
    memset(bytesReturned, 0, 3);
    memset(bytesReadString, 0, 4);
    
    while ((nRead = serial.readBytes(bytesReturned, 3)) > 0) {
        nBytesRead = nRead;
    };
    
    if (nBytesRead > 0) {
        memcpy(bytesReadString, bytesReturned, 3);
        string x = bytesReadString;
        ofLogNotice() << x;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    string msg;
    msg += ofToString(nBytesRead) + " [bytes]" + "\n";
    msg += "read: " + ofToString(bytesReadString);
    ofSetColor(0);
    ofDrawBitmapString(msg, 100, 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
//    string str = "p\n";
//    unsigned char* cstr = (unsigned char*)ofToChar(str);
//    serial.writeBytes(cstr, str.size());
    serial.writeByte('p');
    serial.writeByte('\n');
    ofLogNotice("release");// << str.size();
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
