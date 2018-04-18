#include "drone_Simulator.hpp"

//--------------------------------------------------------------
void DroneSimulator::setup() {
    // window
    ofSetWindowTitle("drone_Simulator");
    ofSetWindowShape(1200, 680);
    ofBackground(170);

    // camera ( X>Y>Z coordinate )
    cam.setDistance(500);
    cam.setFarClip(50000);
    cam.setPosition(0, -3000, 0);
    cam.lookAt(ofVec3f(0, 0, -1));


    for(int i=0; i<100; i++){
        DroneObject* drone = new DroneObject();
        drones.push_back(drone);
        drones[i]->setup();
        drones[i]->setPosRot(ofRandom(-2000, 2000), ofRandom(-2000, 2000), ofRandom(0, 2000), 0, 0, 0);
    }
}

//--------------------------------------------------------------
void DroneSimulator::update() {}

//--------------------------------------------------------------
void DroneSimulator::draw() {
    cam.begin();
    for(int i=0; i<drones.size(); i++){
        drones[i]->draw();
    }
    ofDrawAxis(300); // axis
    cam.end();
}

//--------------------------------------------------------------
void DroneSimulator::keyPressed(int key) {}

//--------------------------------------------------------------
void DroneSimulator::keyReleased(int key) {}

//--------------------------------------------------------------
void DroneSimulator::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void DroneSimulator::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void DroneSimulator::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void DroneSimulator::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void DroneSimulator::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void DroneSimulator::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void DroneSimulator::windowResized(int w, int h) {}

//--------------------------------------------------------------
void DroneSimulator::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void DroneSimulator::dragEvent(ofDragInfo dragInfo) {}
