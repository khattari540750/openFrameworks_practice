#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxUnique2_1.h"

class ofApp : public ofBaseApp{

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofxPanel *_gui;
        ofxUnique2_1 *_unique2_1;
    
        ofParameter<int> _param_ch1;
        ofParameter<int> _param_ch2;
		
};
