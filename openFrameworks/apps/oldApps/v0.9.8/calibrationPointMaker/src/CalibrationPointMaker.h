//!
//! @file DataReaderCalibrationPointGroup.h
//! @brief DataReaderCalibrationPointGroup Xml reader header file
//!

#ifndef CalibrationPointMaker_h
#define CalibrationPointMaker_h

#include "ofMain.h"
#include "ofxTextInputField.h"
#include "ofxXmlSettings.h"

//////////////////////////////////////////////////////////////////////////////////
//// CalibrationPointMaker class
//////////////////////////////////////////////////////////////////////////////////
// class CalibrationPoint {
//  int id;
//  ofVec3f position;
//};

////////////////////////////////////////////////////////////////////////////////
// CalibrationPointMaker class
////////////////////////////////////////////////////////////////////////////////
class CalibrationPointMaker {
public:
  void setup(int num);
  void draw();

  void save();

private:
  map<string, ofxTextInputField *> textField;
  bool isSaved;
};

#endif
