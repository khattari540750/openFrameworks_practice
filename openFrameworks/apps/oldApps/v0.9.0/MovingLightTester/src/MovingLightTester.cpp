#include "MovingLightTester.h"

//--------------------------------------------------------------
void MovingLightTester::setup()
{
    //moving.setDevice("/dev/tty.usbserial-EN167919");
    moving.setDevice("/dev/tty.usbserial-EN174826");
    
    mythos.setStartChannel(10);
    moving.setMovingLight(&mythos);
    
    susharpy.setStartChannel(50);
    moving.setMovingLight(&susharpy);
    
    sharpy.setStartChannel(100);
    moving.setMovingLight(&sharpy);
    
    minibeam.setStartChannel(150);
    moving.setMovingLight(&minibeam);
    
    pointe.setStartChannel(200);
    moving.setMovingLight(&pointe);
    
    moving.startCommunicate();
    
    // window
    ofSetWindowTitle("MovingLightTester");
    ofSetWindowShape(1200, 700);
    
    // Mythos panel
    ofSetVerticalSync(true);
    _mythosPanel.setDefaultWidth(280);
    _mythosPanel.setup("Mythos");
    _mythosPanel.add(_ctrMythosCyanColourWheel.set("CyanColourWheel", 0, 0, 255));
    _mythosPanel.add(_ctrMythosMagentaColourWheel.set("MagentaColourWheel", 0, 0, 255));
    _mythosPanel.add(_ctrMythosYellowColourWheel.set("YellowColourWheel", 0, 0, 255));
    _mythosPanel.add(_ctrMythosColour1.set("Colour1", 0, 0, 255));
    _mythosPanel.add(_ctrMythosColour2.set("Colour2", 0, 0, 255));
    _mythosPanel.add(_ctrMythosColour3.set("Colour3", 0, 0, 255));
    _mythosPanel.add(_ctrMythosStopperStrobe.set("StopperStrobe", 255, 0, 255));
    _mythosPanel.add(_ctrMythosDimmer.set("Dimmer", 0, 0, 255));
    _mythosPanel.add(_ctrMythosDimmerFine.set("DimmerFine", 0, 0, 255));
    _mythosPanel.add(_ctrMythosStaticGoboChange.set("StaticGoboChange", 0, 0, 255));
    _mythosPanel.add(_ctrMythosAnimationDiskInsertion.set("AnimationDiskInsertion", 0, 0, 255));
    _mythosPanel.add(_ctrMythosAnimationDiskRotation.set("AnimationDiskRotation", 0, 0, 255));
    _mythosPanel.add(_ctrMythosRotatingGoboSelect.set("RotatingGoboSelect", 0, 0, 255));
    _mythosPanel.add(_ctrMythosGoboRotation.set("GoboRotation", 0, 0, 255));
    _mythosPanel.add(_ctrMythosFineGoboRotation.set("FineGoboRotation", 0, 0, 255));
    _mythosPanel.add(_ctrMythosPrismsInsertion.set("PrismsInsertion", 0, 0, 255));
    _mythosPanel.add(_ctrMythosPrismsRotation.set("PrismsRotation", 0, 0, 255));
    _mythosPanel.add(_ctrMythosFrost.set("Frost", 0, 0, 255));
    _mythosPanel.add(_ctrMythosZoom.set("Zoom", 0, 0, 255));
    _mythosPanel.add(_ctrMythosFocus.set("Focus", 13, 0, 255));
    _mythosPanel.add(_ctrMythosFocusFine.set("FocusFine", 0, 0, 255));
    _mythosPanel.add(_ctrMythosBeamMode.set("BeamMode", 0, 0, 255));
    _mythosPanel.add(_ctrMythosPan.set("Pan", 43, 0, 255));
    _mythosPanel.add(_ctrMythosFinePan.set("FinePan", 0, 0, 255));
    _mythosPanel.add(_ctrMythosTilt.set("Tilt", 36, 0, 255));
    _mythosPanel.add(_ctrMythosFineTilt.set("FineTilt", 0, 0, 255));
    _mythosPanel.add(_ctrMythosFunction.set("Function", 0, 0, 255));
    _mythosPanel.add(_ctrMythosReset.set("Reset", 0, 0, 255));
    _mythosPanel.add(_ctrMythosLampControl.set("LampControl", 255, 0, 255));
    _mythosPanel.add(_ctrMythosMacroEffects.set("MacroEffects", 0, 0, 255));
    
    // SuperSharpy panel
    ofSetVerticalSync(true);
    _suSharpyPanel.setDefaultWidth(280);
    _suSharpyPanel.setup("SuperSharpy");
    _suSharpyPanel.add(_ctrSuSharpyCyanColourWheel.set("CyanColourWheel", 0, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyMagentaColourWheel.set("MagentaColourWheel", 0, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyYellowColourWheel.set("YellowColourWheel", 0, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyColour1.set("Colour1", 0, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyColour2.set("Colour2", 0, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyColour3.set("Colour3", 0, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyStopperStrobe.set("StopperStrobe", 255, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyDimmer.set("Dimmer", 0, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyDimmerFine.set("DimmerFine", 0, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyStaticGoboChange.set("StaticGoboChange", 0, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyRotatingGoboSelect.set("RotatingGoboSelect", 0, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyGoboRotation.set("GoboRotation", 0, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyFineGoboRotation.set("FineGoboRotation", 0, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyPrismsInsertion.set("PrismsInsertion", 0, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyPrismsRotation.set("PrismsRotation", 0, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyFrost.set("Frost", 0, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyFocus.set("Focus", 32, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyPan.set("Pan", 44, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyFinePan.set("FinePan", 0, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyTilt.set("Tilt", 33, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyFineTilt.set("FineTilt", 0, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyFunction.set("Function", 0, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyReset.set("Reset", 0, 0, 255));
    _suSharpyPanel.add(_ctrSuSharpyLampControl.set("LampControl", 255, 0, 255));
    
    
    // controll panel
    ofSetVerticalSync(true);
    _sharpyPanel.setDefaultWidth(280);
    _sharpyPanel.setup("Sharpy");
    _sharpyPanel.add(_ctrSharpyColourWheel.set("ColourWheel", 0, 0, 255));
    _sharpyPanel.add(_ctrSharpyStopStrobe.set("StopStrobe", 255, 0, 255));
    _sharpyPanel.add(_ctrSharpyDimmer.set("Dimmer", 0, 0, 255));
    _sharpyPanel.add(_ctrSharpyStaticGoboChange.set("StaticGoboChange", 0, 0, 255));
    _sharpyPanel.add(_ctrSharpyPrismInsertion.set("PrismInsertion", 0, 0, 255));
    _sharpyPanel.add(_ctrSharpyPrismRotation.set("PrismRotation", 0, 0, 255));
    _sharpyPanel.add(_ctrSharpyEffectMovement.set("EffectMovement", 0, 0, 255));
    _sharpyPanel.add(_ctrSharpyFrost.set("Frost", 0, 0, 255));
    _sharpyPanel.add(_ctrSharpyFocus.set("Focus", 175, 0, 255));
    _sharpyPanel.add(_ctrSharpyPan.set("Pan", 43, 0, 255));
    _sharpyPanel.add(_ctrSharpyPanFine.set("PanFine", 0, 0, 255));
    _sharpyPanel.add(_ctrSharpyTilt.set("Tilt", 32, 0, 255));
    _sharpyPanel.add(_ctrSharpyTiltFine.set("TiltFine", 0, 0, 255));
    _sharpyPanel.add(_ctrSharpyFunction.set("Function", 0, 0, 255));
    _sharpyPanel.add(_ctrSharpyReset.set("Reset", 0, 0, 255));
    _sharpyPanel.add(_ctrSharpyLampControl.set("LampControl", 255, 0, 255));
    
    
    // MINIBEAM150 panel
    ofSetVerticalSync(true);
    _minibeamPanel.setDefaultWidth(280);
    _minibeamPanel.setup("MINIBEAM150");
    _minibeamPanel.add(_ctrMinibeamPan.set("Pan", 84, 0, 255));
    _minibeamPanel.add(_ctrMinibeamPanFine.set("PanFine", 0, 0, 255));
    _minibeamPanel.add(_ctrMinibeamTilt.set("Tilt", 32, 0, 255));
    _minibeamPanel.add(_ctrMinibeamTiltFine.set("TiltFine", 0, 0, 255));
    _minibeamPanel.add(_ctrMinibeamColorWheel.set("ColorWheel", 0, 0, 255));
    _minibeamPanel.add(_ctrMinibeamGoboWheel1.set("GoboWheel1", 0, 0, 255));
    _minibeamPanel.add(_ctrMinibeamShutter.set("Shutter", 255, 0, 255));
    _minibeamPanel.add(_ctrMinibeamDimmer.set("Dimmer", 0, 0, 255));
    _minibeamPanel.add(_ctrMinibeamFocus.set("Focus", 0, 0, 255));
    _minibeamPanel.add(_ctrMinibeamRotatingPrism.set("RotatingPrism", 0, 0, 255));
    _minibeamPanel.add(_ctrMinibeamFrost.set("Frost", 0, 0, 255));
    _minibeamPanel.add(_ctrMinibeamSpeedPanTilt.set("SpeedPanTilt", 0, 0, 255));
    _minibeamPanel.add(_ctrMinibeamSpecialFunction.set("SpecialFunction", 0, 0, 255));
    
    
    // RobinPointe panel
    ofSetVerticalSync(true);
    _pointePanel.setDefaultWidth(280);
    _pointePanel.setup("RobePointe");
    _pointePanel.add(_ctrPointePan.set("Pan", 43, 0, 255));
    _pointePanel.add(_ctrPointePanFine.set("PanFine", 0, 0, 255));
    _pointePanel.add(_ctrPointeTilt.set("Tilt", 39, 0, 255));
    _pointePanel.add(_ctrPointeTiltFine.set("TiltFine", 0, 0, 255));
    _pointePanel.add(_ctrPointePanTiltSpeedTime.set("PanTiltSpeedTime", 0, 0, 255));
    _pointePanel.add(_ctrPointePowerSpecialFunctions.set("PowerSpecialFunctions", 130, 0, 255));
    _pointePanel.add(_ctrPointeColourWheel.set("ColourWheel", 0, 0, 255));
    _pointePanel.add(_ctrPointeColourWheelFinePositioning.set("ColourWheelFinePositioning", 0, 0, 255));
    _pointePanel.add(_ctrPointeEffectSpeed.set("EffectSpeed", 0, 0, 255));
    _pointePanel.add(_ctrPointeStaticGoboWheel.set("StaticGoboWheel", 0, 0, 255));
    _pointePanel.add(_ctrPointeRotationGoboWheel.set("RotationGoboWheel", 0, 0, 255));
    _pointePanel.add(_ctrPointeRotGoboIndexingAndRotation.set("RotGoboIndexingAndRotation", 0, 0, 255));
    _pointePanel.add(_ctrPointeRotGoboIndexingAndRotationFine.set("RotGoboIndexingAndRotationFine", 0, 0, 255));
    _pointePanel.add(_ctrPointePrism.set("Prism", 0, 0, 255));
    _pointePanel.add(_ctrPointePrismRotationAndIndexing.set("PrismRotationAndIndexing", 0, 0, 255));
    _pointePanel.add(_ctrPointeFrost.set("Frost", 0, 0, 255));
    _pointePanel.add(_ctrPointeZoom.set("Zoom", 255, 0, 255));
    _pointePanel.add(_ctrPointeZoomFine.set("ZoomFine", 0, 0, 255));
    _pointePanel.add(_ctrPointeFocus.set("Focus", 0, 0, 255));
    _pointePanel.add(_ctrPointeFocusFine.set("FocusFine", 0, 0, 255));
    _pointePanel.add(_ctrPointeAutoFocus.set("AutoFocus", 0, 0, 255));
    _pointePanel.add(_ctrPointeShutterStrobe.set("ShutterStrobe", 255, 0, 255));
    _pointePanel.add(_ctrPointeDimmerIntensity.set("DimmerIntensity", 0, 0, 255));
    _pointePanel.add(_ctrPointeDimmerIntensityFine.set("DimmerIntensityFine", 0, 0, 255));
}


//--------------------------------------------------------------
void MovingLightTester::update()
{
    if(moving.isConnected()) {
        moving.update();
    }
    
    // mythos
    mythos.channelCyanColourWheel(_ctrMythosCyanColourWheel);
    mythos.channelMagentaColourWheel(_ctrMythosMagentaColourWheel);
    mythos.channelYellowColourWheel(_ctrMythosYellowColourWheel);
    mythos.channelColour1(_ctrMythosColour1);
    mythos.channelColour2(_ctrMythosColour2);
    mythos.channelColour3(_ctrMythosColour3);
    mythos.channelStopperStrobe(_ctrMythosStopperStrobe);
    mythos.channelDimmer(_ctrMythosDimmer);
    mythos.channelDimmerFine(_ctrMythosDimmerFine);
    mythos.channelStaticGoboChange(_ctrMythosStaticGoboChange);
    mythos.channelAnimationDiskInsertion(_ctrMythosAnimationDiskInsertion);
    mythos.channelAnimationDiskRotation(_ctrMythosAnimationDiskRotation);
    mythos.channelRotatingGoboSelect(_ctrMythosRotatingGoboSelect);
    mythos.channelGoboRotation(_ctrMythosGoboRotation);
    mythos.channelFineGoboRotation(_ctrMythosFineGoboRotation);
    mythos.channelPrismsInsertion(_ctrMythosPrismsInsertion);
    mythos.channelPrismsRotation(_ctrMythosPrismsRotation);
    mythos.channelFrost(_ctrMythosFrost);
    mythos.channelZoom(_ctrMythosZoom);
    mythos.channelFocus(_ctrMythosFocus);
    mythos.channelFocusFine(_ctrMythosFocusFine);
    mythos.channelBeamMode(_ctrMythosBeamMode);
    mythos.channelPan(_ctrMythosPan);
    mythos.channelFinePan(_ctrMythosFinePan);
    mythos.channelTilt(_ctrMythosTilt);
    mythos.channelFineTilt(_ctrMythosFineTilt);
    mythos.channelFunction(_ctrMythosFunction);
    mythos.channelReset(_ctrMythosReset);
    mythos.channelLampControl(_ctrMythosLampControl);
    mythos.channelMacroEffects(_ctrMythosMacroEffects);
    
    //sharpy
    sharpy.channelColourWheel(_ctrSharpyColourWheel);
    sharpy.channelStopStrobe(_ctrSharpyStopStrobe);
    sharpy.channelDimmer(_ctrSharpyDimmer);
    sharpy.channelStaticGoboChange(_ctrSharpyStaticGoboChange);
    sharpy.channelPrismInsertion(_ctrSharpyPrismInsertion);
    sharpy.channelPrismRotation(_ctrSharpyPrismRotation);
    sharpy.channelEffectMovement(_ctrSharpyEffectMovement);
    sharpy.channelFrost(_ctrSharpyFrost);
    sharpy.channelFocus(_ctrSharpyFocus);
    sharpy.channelPan(_ctrSharpyPan);
    sharpy.channelPanFine(_ctrSharpyPanFine);
    sharpy.channelTilt(_ctrSharpyTilt);
    sharpy.channelTiltFine(_ctrSharpyTiltFine);
    sharpy.channelFunction(_ctrSharpyFunction);
    sharpy.channelReset(_ctrSharpyReset);
    sharpy.channelLampControl(_ctrSharpyLampControl);
    
    //super sharpy
    susharpy.channelCyanColourWheel(_ctrSuSharpyCyanColourWheel);
    susharpy.channelMagentaColourWheel(_ctrSuSharpyMagentaColourWheel);
    susharpy.channelYellowColourWheel(_ctrSuSharpyYellowColourWheel);
    susharpy.channelColour1(_ctrSuSharpyColour1);
    susharpy.channelColour2(_ctrSuSharpyColour2);
    susharpy.channelColour3(_ctrSuSharpyColour3);
    susharpy.channelStopperStrobe(_ctrSuSharpyStopperStrobe);
    susharpy.channelDimmer(_ctrSuSharpyDimmer);
    susharpy.channelDimmerFine(_ctrSuSharpyDimmerFine);
    susharpy.channelStaticGoboChange(_ctrSuSharpyStaticGoboChange);
    susharpy.channelRotatingGoboSelect(_ctrSuSharpyRotatingGoboSelect);
    susharpy.channelGoboRotation(_ctrSuSharpyGoboRotation);
    susharpy.channelFineGoboRotation(_ctrSuSharpyFineGoboRotation);
    susharpy.channelPrismsInsertion(_ctrSuSharpyPrismsInsertion);
    susharpy.channelPrismsRotation(_ctrSuSharpyPrismsRotation);
    susharpy.channelFrost(_ctrSuSharpyFrost);
    susharpy.channelFocus(_ctrSuSharpyFocus);
    susharpy.channelPan(_ctrSuSharpyPan);
    susharpy.channelFinePan(_ctrSuSharpyFinePan);
    susharpy.channelTilt(_ctrSuSharpyTilt);
    susharpy.channelFineTilt(_ctrSuSharpyFineTilt);
    susharpy.channelFunction(_ctrSuSharpyFunction);
    susharpy.channelReset(_ctrSuSharpyReset);
    susharpy.channelLampControl(_ctrSuSharpyLampControl);
    
    // minibeam
    minibeam.channelPan(_ctrMinibeamPan);
    minibeam.channelPanFine(_ctrMinibeamPanFine);
    minibeam.channelTilt(_ctrMinibeamTilt);
    minibeam.channelTiltFine(_ctrMinibeamTiltFine);
    minibeam.channelColorWheel(_ctrMinibeamColorWheel);
    minibeam.channelGoboWheel1(_ctrMinibeamGoboWheel1);
    minibeam.channelShutter(_ctrMinibeamShutter);
    minibeam.channelDimmer(_ctrMinibeamDimmer);
    minibeam.channelFocus(_ctrMinibeamFocus);
    minibeam.channelRotatingPrism(_ctrMinibeamRotatingPrism);
    minibeam.channelFrost(_ctrMinibeamFrost);
    minibeam.channelSpeedPanTilt(_ctrMinibeamSpeedPanTilt);
    minibeam.channelSpecialFunction(_ctrMinibeamSpecialFunction);
    
    // RobinPointe
    pointe.channelPan(_ctrPointePan);
    pointe.channelPanFine(_ctrPointePanFine);
    pointe.channelTilt(_ctrPointeTilt);
    pointe.channelTiltFine(_ctrPointeTiltFine);
    pointe.channelPanTiltSpeedTime(_ctrPointePanTiltSpeedTime);
    pointe.channelPowerSpecialFunctions(_ctrPointePowerSpecialFunctions);
    pointe.channelColourWheel(_ctrPointeColourWheel);
    pointe.channelColourWheelFinePositioning( _ctrPointeColourWheelFinePositioning);
    pointe.channelEffectSpeed(_ctrPointeEffectSpeed);
    pointe.channelStaticGoboWheel(_ctrPointeStaticGoboWheel);
    pointe.channelRotationGoboWheel(_ctrPointeRotationGoboWheel);
    pointe.channelRotGoboIndexingAndRotation(_ctrPointeRotGoboIndexingAndRotation);
    pointe.channelRotGoboIndexingAndRotationFine(_ctrPointeRotGoboIndexingAndRotationFine);
    pointe.channelPrism(_ctrPointePrism);
    pointe.channelPrismRotationAndIndexing(_ctrPointePrismRotationAndIndexing);
    pointe.channelFrost(_ctrPointeFrost);
    pointe.channelZoom(_ctrPointeZoom);
    pointe.channelZoomFine(_ctrPointeZoomFine);
    pointe.channelFocus(_ctrPointeFocus);
    pointe.channelFocusFine(_ctrPointeFocusFine);
    pointe.channelAutoFocus(_ctrPointeAutoFocus);
    pointe.channelShutterStrobe(_ctrPointeShutterStrobe);
    pointe.channelDimmerIntensity(_ctrPointeDimmerIntensity);
    pointe.channelDimmerIntensityFine(_ctrPointeDimmerIntensityFine);
}


//--------------------------------------------------------------
void MovingLightTester::draw()
{
    ofBackgroundGradient(ofColor::gray, ofColor::black);
    
    _mythosPanel.draw();
    _suSharpyPanel.draw();
    _sharpyPanel.draw();
    _minibeamPanel.draw();
    _pointePanel.draw();
    
    ofDrawBitmapString("FPS : " + ofToString(ofGetFrameRate()), ofPoint(10, ofGetWindowHeight()-10));
}




