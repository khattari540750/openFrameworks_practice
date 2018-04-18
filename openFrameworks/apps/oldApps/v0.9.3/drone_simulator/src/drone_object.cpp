#include "drone_object.hpp"

DroneObject::DroneObject() {
  bodyObj = new ofBoxPrimitive();
  rightRotorObj = new ofCylinderPrimitive();
  leftRotorObj = new ofCylinderPrimitive();
  frontRotorObj = new ofCylinderPrimitive();
  backRotorObj = new ofCylinderPrimitive();
  arm1Obj = new ofBoxPrimitive();
  arm2Obj = new ofBoxPrimitive();
  frontMarkerObj = new ofBoxPrimitive();
}

DroneObject::~DroneObject() {
  if (bodyObj)
    delete bodyObj;
  if (rightRotorObj)
    delete rightRotorObj;
  if (leftRotorObj)
    delete leftRotorObj;
  if (frontRotorObj)
    delete frontRotorObj;
  if (backRotorObj)
    delete backRotorObj;
  if (arm1Obj)
    delete arm1Obj;
  if (arm2Obj)
    delete arm2Obj;
  if (frontMarkerObj)
    delete frontMarkerObj;
}

void DroneObject::setup() {
  bodyColor = ofColor(0, 150);
  bodyObj->set(35, 58, 5);

  armColor = ofColor(0, 150);
  arm1Obj->set(100, 5, 3);
  arm2Obj->set(100, 5, 3);

  rotorColor = ofColor(250, 120);
  rightRotorObj->set(20, 1);
  leftRotorObj->set(20, 1);
  frontRotorObj->set(20, 1);
  backRotorObj->set(20, 1);
  rightRotorObj->setResolutionRadius(10);
  leftRotorObj->setResolutionRadius(10);
  frontRotorObj->setResolutionRadius(10);
  backRotorObj->setResolutionRadius(10);

  frontMarkerColor = ofColor(255, 180, 0, 200);
  frontMarkerObj->set(1, 25, 5);
}

void DroneObject::draw() {
  ofPushMatrix();

  ofTranslate(posX, posY, posZ);
  ofRotateZ(rotZ);
  ofRotateY(rotY);
  ofRotateX(rotX);

  drawBodyObj();
  drawArm1Obj();
  drawArm2Obj();
  drawRightRotorObj();
  drawLeftRotorObj();
  drawFrontRotorObj();
  drawBackRotorObj();
  drawFrontMarkerObj();
  ofDrawAxis(50);
  ofPopMatrix();
}

void DroneObject::setPosRot(float posX, float posY, float posZ, float rotX,
                            float rotY, float rotZ) {
  this->posX = posX;
  this->posY = posY;
  this->posZ = posZ;
  this->rotX = rotX;
  this->rotY = rotY;
  this->rotZ = rotZ;
}

void DroneObject::drawBodyObj() {
  ofPushMatrix();
  ofSetColor(bodyColor);
  bodyObj->draw();
  ofPopMatrix();
}

void DroneObject::drawRightRotorObj() {
  ofPushMatrix();
  ofSetColor(rotorColor);
  ofRotateX(90);
  ofTranslate(0, bodyObj->getDepth() + arm1Obj->getDepth(),
              arm1Obj->getWidth() / 2);
  frontRotorObj->draw();
  ofPopMatrix();
}

void DroneObject::drawLeftRotorObj() {
  ofPushMatrix();
  ofSetColor(rotorColor);
  ofRotateX(90);
  ofTranslate(0, bodyObj->getDepth() + arm1Obj->getDepth(),
              -arm1Obj->getWidth() / 2);
  frontRotorObj->draw();
  ofPopMatrix();
}

void DroneObject::drawFrontRotorObj() {
  ofPushMatrix();
  ofSetColor(rotorColor);
  ofRotateX(90);
  ofTranslate(arm1Obj->getWidth() / 2,
              bodyObj->getDepth() + arm1Obj->getDepth(), 0);
  frontRotorObj->draw();
  ofPopMatrix();
}

void DroneObject::drawBackRotorObj() {
  ofPushMatrix();
  ofSetColor(rotorColor);
  ofRotateX(90);
  ofTranslate(-arm1Obj->getWidth() / 2,
              bodyObj->getDepth() + arm1Obj->getDepth(), 0);
  frontRotorObj->draw();
  ofPopMatrix();
}

void DroneObject::drawArm1Obj() {
  ofPushMatrix();
  ofSetColor(armColor);
  ofTranslate(0, 0, bodyObj->getDepth());
  arm1Obj->draw();
  ofPopMatrix();
}

void DroneObject::drawArm2Obj() {
  ofPushMatrix();
  ofSetColor(armColor);
  ofRotateZ(90);
  ofTranslate(0, 0, bodyObj->getDepth());
  arm2Obj->draw();
  ofPopMatrix();
}

void DroneObject::drawFrontMarkerObj() {
  ofPushMatrix();
  ofSetColor(frontMarkerColor);
  ofTranslate(bodyObj->getWidth() / 2, 0, 0);
  frontMarkerObj->draw();
  ofPopMatrix();
}
