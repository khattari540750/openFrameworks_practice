#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"

#define TEXTURE_ALLOCATE_WIDTH 720
#define TEXTURE_ALLOCATE_HEIGHT 16

#define BLANK_SPACE 30
#define BLANK_TOTAL 2

class CDJ2015_SyphonServerTester : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyReleased(int key);
		void mouseReleased(int x, int y, int button);
		
    // server
    ofxSyphonServer *_server1;
    ofxSyphonServer *_server2;
    ofxSyphonServer *_server3;
    string SERVER_NAME_1 = "1";
    string SERVER_NAME_2 = "2";
    string SERVER_NAME_3 = "3";
    
    // texture
    ofTexture *_tex1;
    ofTexture *_tex2;
    ofTexture *_tex3;
    
    // rectangle
    vector<float> _rectAlphas;
    int RECT_WIDTH = 240;
    int RECT_HEIGHT = 16;
    int RECT_TOTAL = 3;
    
    // position
    ofPoint _pos_tex1;
    ofPoint _pos_tex2;
    ofPoint _pos_tex3;
    
    // flag
    bool GUIDE;
};
