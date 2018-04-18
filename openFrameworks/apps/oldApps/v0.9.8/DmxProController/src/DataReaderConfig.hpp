//
//  DataReaderConfig.hpp
//  DmxProController
//

#ifndef DataReaderConfig_hpp
#define DataReaderConfig_hpp

#include "ofMain.h"
#include "ofxXmlSettings.h"

class DataReaderConfig {
public:
  DataReaderConfig();
  ~DataReaderConfig();

public:
  void loadXml(string path);

public:
  int windowWidth;
  int windowHeight;

  string dmxPath;
  int dmxChannelTotal;
};

#endif
