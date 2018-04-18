//
//  main.cpp
//  example_sharpyConcentration
//
//  Created by HATTORI Kohei on 2016/02/29.
//
//



#include "ofMain.h"
#include "example_sharpyConcentration.h"



//==============================================================
// main function
//==============================================================
int main( )
{
    ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new example_sharpyConcentration());
}
