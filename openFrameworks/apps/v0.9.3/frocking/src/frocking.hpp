#pragma once

#include "ofMain.h"
#include "particle.hpp"
#include "ofxGui.h"


/*
class Frocking : public ofBaseApp
{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
private:
    
private: // moving head light control panel variables
    ofxPanel controlPanel;
    ofParameter<float>  cohesionStrength;
    ofParameter<int>    cohesionRadius;
    ofParameter<float>  alignmentStrength;
    ofParameter<int>    alignmentRadius;
    ofParameter<float>  seperationStrength;
    ofParameter<int>    seperationRadius;
    ofParameter<float>  damping;
    ofParameter<float>  attractionStrength;
    ofParameter<int>    attractionRadius;
    
    repulsive
};
*/



 
 
 
class Frocking : public ofBaseApp
{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
private:
    vector <particle> particles;
    
    
private: // moving head light control panel variables
    ofxPanel controlPanel;
    ofParameter<float> cohesionStrength;
    ofParameter<int> cohesionRadius;
    ofParameter<float> alignmentStrength;
    ofParameter<int> alignmentRadius;
    ofParameter<float> seperationStrength;
    ofParameter<int> seperationRadius;
    ofParameter<float> damping;
};





























/*
class ofApp : public ofBaseApp
{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
private:
    ofEasyCam cam;
    vector <particle> particles;
    
    
private: // moving head light control panel variables
    ofxPanel controlPanel;
    ofParameter<float> cohesionStrength;
    ofParameter<int> cohesionRadius;
    ofParameter<float> alignmentStrength;
    ofParameter<int> alignmentRadius;
    ofParameter<float> seperationStrength;
    ofParameter<int> seperationRadius;
    ofParameter<float> damping;
};
*/