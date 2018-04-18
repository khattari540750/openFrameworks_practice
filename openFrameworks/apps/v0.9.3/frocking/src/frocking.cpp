#include "frocking.hpp"



//--------------------------------------------------------------
void Frocking::setup()
{
    // app setup
    ofBackground(0, 0, 0);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    // particle setup
    for (int i = 0; i < 600; i++){
        particle myParticle;
        myParticle.setInitialCondition(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
        particles.push_back(myParticle);
    }
    
    // pannel setup
    controlPanel.setDefaultWidth(700);
    controlPanel.setup("flocking");
    controlPanel.add(cohesionStrength.set("cohesion strength", 0.01,0,1));
    controlPanel.add(cohesionRadius.set("cohesion radius", 50,0,200));
    controlPanel.add(alignmentStrength.set("alignment strength", 0.01,0,1));
    controlPanel.add(alignmentRadius.set("alignment radius", 50,0,200));
    controlPanel.add(seperationStrength.set("seperation strength", 0.01,0, 1));
    controlPanel.add(seperationRadius.set("seperation radius", 50,0,200));
    controlPanel.add(damping.set("damping", 0.01, 0.001, 0.5));
}



//--------------------------------------------------------------
void Frocking::update()
{
    for (int i = 0; i < particles.size(); i++){
        particles[i].cohesion.distance = cohesionRadius;
        particles[i].alignment.distance = alignmentRadius;
        particles[i].seperation.distance = seperationRadius;
        
        particles[i].cohesion.strength = cohesionStrength;
        particles[i].alignment.strength = alignmentStrength;
        particles[i].seperation.strength = seperationStrength;
        
        particles[i].damping = damping;
    }
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].resetForce();
    }
    
    for (int i = 0; i < particles.size(); i++){
        for (int j = 0; j < particles.size(); j++){
            if (i != j){
                particles[i].addForFlocking(particles[j]);
            }
        }
        // this was something we tried in class (partitcle move away from mouse...)
        particles[i].addRepulsionForce(mouseX, mouseY, 40, 0.4);
        particles[i].addAttractionForce(ofGetWidth()/2, ofGetHeight()/2, 600, 0.07);
    }
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].addFlockingForce();
        particles[i].addDampingForce();
        particles[i].update();
    }
    
    
    // wrap torroidally.
    for (int i = 0; i < particles.size(); i++){
        ofVec2f pos = particles[i].pos;
        if (pos.x < 0) pos.x = ofGetWidth();
        if (pos.x > ofGetWidth()) pos.x = 0;
        if (pos.y < 0) pos.y = ofGetHeight();
        if (pos.y > ofGetHeight()) pos.y = 0;
        particles[i].pos = pos;
    }
    
}


//--------------------------------------------------------------
void Frocking::draw()
{
    ofEnableAlphaBlending();
    ofSetColor(0,130,130, 200);
    
    ofSetColor(0xffffff);
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].draw();
    }
    
    controlPanel.draw();
}


//--------------------------------------------------------------
void Frocking::keyPressed(int key)
{
    switch (key){
            
        case ' ':
            // reposition everything:
            for (int i = 0; i < particles.size(); i++){
                particles[i].setInitialCondition(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
            }
            break;
    }
}


//--------------------------------------------------------------
void Frocking::keyReleased(int key){
    
}


//--------------------------------------------------------------
void Frocking::mouseMoved(int x, int y ){
    
}


//--------------------------------------------------------------
void Frocking::mouseDragged(int x, int y, int button)
{
    if (x < 500){
        particles.erase(particles.begin());
        particle myParticle;
        float randomAngle = ofRandom(0, TWO_PI);
        myParticle.setInitialCondition(x,y,cos(randomAngle),sin(randomAngle));
        particles.push_back(myParticle);
    }
}


//--------------------------------------------------------------
void Frocking::mousePressed(int x, int y, int button)
{
    
}


//--------------------------------------------------------------
void Frocking::mouseReleased(int x, int y, int button)
{
    
}


//--------------------------------------------------------------
void Frocking::mouseEntered(int x, int y)
{
    
}


//--------------------------------------------------------------
void Frocking::mouseExited(int x, int y)
{
    
}


//--------------------------------------------------------------
void Frocking::windowResized(int w, int h)
{
    
}


//--------------------------------------------------------------
void Frocking::gotMessage(ofMessage msg)
{
    
}


//--------------------------------------------------------------
void Frocking::dragEvent(ofDragInfo dragInfo)
{
    
}










