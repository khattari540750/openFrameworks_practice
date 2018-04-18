//
//  particle.hpp
//  frocking
//
//  Created by 服部 弘平 on 2016/03/28.
//
//

#ifndef particle_hpp
#define particle_hpp



#include "ofMain.h"



typedef struct
{
    int count;
    ofVec2f	sum;
    float distance;
    float strength;
} flockingForce;



class particle
{
public:
    particle();
    virtual ~particle(){};
    
    void resetForce();
    void addForce(float x, float y);
    void addRepulsionForce(float x, float y, float radius, float scale);
    void addAttractionForce(float x, float y, float radius, float scale);
    
    void addRepulsionForce(particle &p, float radius, float scale);
    void addAttractionForce(particle &p, float radius, float scale);
    void addClockwiseForce(particle &p, float radius, float scale);
    void addCounterClockwiseForce(particle &p, float radius, float scale);
    
    void addDampingForce();
    
    void addForFlocking(particle &p);
    void addFlockingForce();
    
    void setInitialCondition(float px, float py, float vx, float vy);
    void update();
    void draw();
    
    void bounceOffWalls();
    
    
public:
    flockingForce cohesion;
    flockingForce seperation;
    flockingForce alignment;
    
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f frc;   // frc is also know as acceleration (newton says "f=ma")
    
    float damping;
};



#endif














/*

typedef struct
{
    int count;
    ofVec3f sum;
    float distance;
    float strength;
} flockingForce;



class particle
{
public:
    particle();
    virtual ~particle(){};
    
    void update();
    void draw();
    
    void resetForce();
    void addForce(float x, float y, float z);
    void addRepulsionForce(float x, float y, float z, float radius, float scale);
    void addAttractionForce(float x, float y, float z, float radius, float scale);
    void addRepulsionForce(particle &p, float radius, float scale);
    void addAttractionForce(particle &p, float radius, float scale);
    void addClockwiseForce(particle &p, float radius, float scale);
    void addCounterClockwiseForce(particle &p, float radius, float scale);
    void addDampingForce();
    void addForFlocking(particle &p);
    void addFlockingForce();
    
    void bounceOffWalls();
    
    
private:
    void setInitialCondition(float px, float py, float pz,
                             float vx, float vy, float vz);
    
 
public:
    flockingForce cohesion;
    flockingForce seperation;
    flockingForce alignment;
    
    ofVec3f pos;
    ofVec3f vel;
    ofVec3f frc;
    
    float damping;
    

private:
    ofSpherePrimitive* obj;
};

*/
