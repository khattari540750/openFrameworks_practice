#ifndef DRONE_OBJECT_HPP
#define DRONE_OBJECT_HPP

#include "ofMain.h"

class DroneObject {
public:
  DroneObject();
  ~DroneObject();

  void setup();
  void draw();

  void setPosRot(float posX, float posY, float posZ, float rotX, float rotY,
                 float rotZ);

private:
  void drawBodyObj();
  void drawRightRotorObj();
  void drawLeftRotorObj();
  void drawFrontRotorObj();
  void drawBackRotorObj();
  void drawArm1Obj();
  void drawArm2Obj();
  void drawFrontMarkerObj();

private:
  ofBoxPrimitive *bodyObj;
  ofCylinderPrimitive *rightRotorObj;
  ofCylinderPrimitive *leftRotorObj;
  ofCylinderPrimitive *frontRotorObj;
  ofCylinderPrimitive *backRotorObj;
  ofBoxPrimitive *arm1Obj;
  ofBoxPrimitive *arm2Obj;
  ofBoxPrimitive *frontMarkerObj;

  ofColor bodyColor;
  ofColor rotorColor;
  ofColor armColor;
  ofColor frontMarkerColor;

  float posX;
  float posY;
  float posZ;
  float rotX;
  float rotY;
  float rotZ;
};

#endif // DRONE_OBJECT_HPP
