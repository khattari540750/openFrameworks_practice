#pragma once

#include "ofMain.h"
#include "ofxMovingLight.h"
#include "movingLightDrivers/Mythos.h"
#include "movingLightDrivers/SuperSharpy.h"
#include "movingLightDrivers/Sharpy.h"
#include "movingLightDrivers/MINIBEAM150.h"
#include "movingLightDrivers/RobinPointe.h"
#include "ofxGui.h"



class MovingLightTester : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    
private:
    ofxMovingLight moving;
    Mythos mythos;
    SuperSharpy susharpy;
    Sharpy sharpy;
    MINIBEAM150 minibeam;
    RobinPointe pointe;
    
    
private: // Mythos controll panel
    ofxPanel _mythosPanel;
    ofParameter<int> _ctrMythosCyanColourWheel;
    ofParameter<int> _ctrMythosMagentaColourWheel;
    ofParameter<int> _ctrMythosYellowColourWheel;
    ofParameter<int> _ctrMythosColour1;
    ofParameter<int> _ctrMythosColour2;
    ofParameter<int> _ctrMythosColour3;
    ofParameter<int> _ctrMythosStopperStrobe;
    ofParameter<int> _ctrMythosDimmer;
    ofParameter<int> _ctrMythosDimmerFine;
    ofParameter<int> _ctrMythosStaticGoboChange;
    ofParameter<int> _ctrMythosAnimationDiskInsertion;
    ofParameter<int> _ctrMythosAnimationDiskRotation;
    ofParameter<int> _ctrMythosRotatingGoboSelect;
    ofParameter<int> _ctrMythosGoboRotation;
    ofParameter<int> _ctrMythosFineGoboRotation;
    ofParameter<int> _ctrMythosPrismsInsertion;
    ofParameter<int> _ctrMythosPrismsRotation;
    ofParameter<int> _ctrMythosFrost;
    ofParameter<int> _ctrMythosZoom;
    ofParameter<int> _ctrMythosFocus;
    ofParameter<int> _ctrMythosFocusFine;
    ofParameter<int> _ctrMythosBeamMode;
    ofParameter<int> _ctrMythosPan;
    ofParameter<int> _ctrMythosFinePan;
    ofParameter<int> _ctrMythosTilt;
    ofParameter<int> _ctrMythosFineTilt;
    ofParameter<int> _ctrMythosFunction;
    ofParameter<int> _ctrMythosReset;
    ofParameter<int> _ctrMythosLampControl;
    ofParameter<int> _ctrMythosMacroEffects;
    
    
private: // superSharpy panel
    ofxPanel _suSharpyPanel;
    ofParameter<int> _ctrSuSharpyCyanColourWheel;
    ofParameter<int> _ctrSuSharpyMagentaColourWheel;
    ofParameter<int> _ctrSuSharpyYellowColourWheel;
    ofParameter<int> _ctrSuSharpyColour1;
    ofParameter<int> _ctrSuSharpyColour2;
    ofParameter<int> _ctrSuSharpyColour3;
    ofParameter<int> _ctrSuSharpyStopperStrobe;
    ofParameter<int> _ctrSuSharpyDimmer;
    ofParameter<int> _ctrSuSharpyDimmerFine;
    ofParameter<int> _ctrSuSharpyStaticGoboChange;
    ofParameter<int> _ctrSuSharpyRotatingGoboSelect;
    ofParameter<int> _ctrSuSharpyGoboRotation;
    ofParameter<int> _ctrSuSharpyFineGoboRotation;
    ofParameter<int> _ctrSuSharpyPrismsInsertion;
    ofParameter<int> _ctrSuSharpyPrismsRotation;
    ofParameter<int> _ctrSuSharpyFrost;
    ofParameter<int> _ctrSuSharpyFocus;
    ofParameter<int> _ctrSuSharpyPan;
    ofParameter<int> _ctrSuSharpyFinePan;
    ofParameter<int> _ctrSuSharpyTilt;
    ofParameter<int> _ctrSuSharpyFineTilt;
    ofParameter<int> _ctrSuSharpyFunction;
    ofParameter<int> _ctrSuSharpyReset;
    ofParameter<int> _ctrSuSharpyLampControl;
    
    
private: // sharpy panel
    ofxPanel _sharpyPanel;
    ofParameter<int> _ctrSharpyColourWheel;
    ofParameter<int> _ctrSharpyStopStrobe;
    ofParameter<int> _ctrSharpyDimmer;
    ofParameter<int> _ctrSharpyStaticGoboChange;
    ofParameter<int> _ctrSharpyPrismInsertion;
    ofParameter<int> _ctrSharpyPrismRotation;
    ofParameter<int> _ctrSharpyEffectMovement;
    ofParameter<int> _ctrSharpyFrost;
    ofParameter<int> _ctrSharpyFocus;
    ofParameter<int> _ctrSharpyPan;
    ofParameter<int> _ctrSharpyPanFine;
    ofParameter<int> _ctrSharpyTilt;
    ofParameter<int> _ctrSharpyTiltFine;
    ofParameter<int> _ctrSharpyFunction;
    ofParameter<int> _ctrSharpyReset;
    ofParameter<int> _ctrSharpyLampControl;
    
    
private: // minibeam controller
    ofxPanel _minibeamPanel;
    ofParameter<int> _ctrMinibeamPan;
    ofParameter<int> _ctrMinibeamPanFine;
    ofParameter<int> _ctrMinibeamTilt;
    ofParameter<int> _ctrMinibeamTiltFine;
    ofParameter<int> _ctrMinibeamColorWheel;
    ofParameter<int> _ctrMinibeamGoboWheel1;
    ofParameter<int> _ctrMinibeamShutter;
    ofParameter<int> _ctrMinibeamDimmer;
    ofParameter<int> _ctrMinibeamFocus;
    ofParameter<int> _ctrMinibeamRotatingPrism;
    ofParameter<int> _ctrMinibeamFrost;
    ofParameter<int> _ctrMinibeamSpeedPanTilt;
    ofParameter<int> _ctrMinibeamSpecialFunction;
    
    
private: // pointe panel
    ofxPanel _pointePanel;
    ofParameter<int> _ctrPointePan;
    ofParameter<int> _ctrPointePanFine;
    ofParameter<int> _ctrPointeTilt;
    ofParameter<int> _ctrPointeTiltFine;
    ofParameter<int> _ctrPointePanTiltSpeedTime;
    ofParameter<int> _ctrPointePowerSpecialFunctions;
    ofParameter<int> _ctrPointeColourWheel;
    ofParameter<int> _ctrPointeColourWheelFinePositioning;
    ofParameter<int> _ctrPointeEffectSpeed;
    ofParameter<int> _ctrPointeStaticGoboWheel;
    ofParameter<int> _ctrPointeRotationGoboWheel;
    ofParameter<int> _ctrPointeRotGoboIndexingAndRotation;
    ofParameter<int> _ctrPointeRotGoboIndexingAndRotationFine;
    ofParameter<int> _ctrPointePrism;
    ofParameter<int> _ctrPointePrismRotationAndIndexing;
    ofParameter<int> _ctrPointeFrost;
    ofParameter<int> _ctrPointeZoom;
    ofParameter<int> _ctrPointeZoomFine;
    ofParameter<int> _ctrPointeFocus;
    ofParameter<int> _ctrPointeFocusFine;
    ofParameter<int> _ctrPointeAutoFocus;
    ofParameter<int> _ctrPointeShutterStrobe;
    ofParameter<int> _ctrPointeDimmerIntensity;
    ofParameter<int> _ctrPointeDimmerIntensityFine;
    
};
