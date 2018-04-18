//
//  DataReaderConfig.cpp
//  DmxProController
//

#include "DataReaderConfig.hpp"

#include "DataReaderConfig.hpp"

//--------------------------------------------------------------
DataReaderConfig::DataReaderConfig() {}

//--------------------------------------------------------------
DataReaderConfig::~DataReaderConfig() {}

//--------------------------------------------------------------
void DataReaderConfig::loadXml(string path) {
  ofxXmlSettings xml;
  xml.loadFile(path);
    
  xml.pushTag("config");

  windowWidth = xml.getValue("window_width", 1000);
  windowHeight = xml.getValue("window_height", 500);

  dmxPath = xml.getValue("dmx_path", "");
  dmxChannelTotal = xml.getValue("dmx_channel_total", 5);
}