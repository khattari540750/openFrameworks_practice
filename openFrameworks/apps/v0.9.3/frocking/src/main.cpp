#include "ofMain.h"
#include "frocking.hpp"



//========================================================================
int main( )
{
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
	ofRunApp(new Frocking());
}
