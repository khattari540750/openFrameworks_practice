#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

  {
    // config file read
    dataReaderConfig.loadXml("config.xml");
  }

  {
    // window
    int width = dataReaderConfig.windowWidth;
    int height = dataReaderConfig.windowHeight;
    ofSetWindowShape(width, height);
  }

  {
    // dmx
    dmx.connect(dataReaderConfig.dmxPath, 512); // use the name
  }

  {
    ofSetVerticalSync(true);
    panel.setup();
    panel.setName(dataReaderConfig.dmxPath);

    // check cnannel
    int channelTotal = dataReaderConfig.dmxChannelTotal;
    if (channelTotal > 512)
      channelTotal = 512;

    // add sliders to panel
    for (int i = 0; i < channelTotal; i++) {
      ofParameter<int> chan;
      chanList.push_back(chan);
      string str = "channel " + ofToString(i + 1);
      chan.set(str, 0, 0, 255);
      panel.add(chan);
    }
  }
}

//--------------------------------------------------------------
void ofApp::exit() {
  {
    // dmx
    dmx.clear();
    dmx.update(true); // black on shutdown
  }
}

//--------------------------------------------------------------
void ofApp::update() {

  // dmx
  for (int i = 0; i < chanList.size(); i++) {
      dmx.setLevel(1 + i, chanList[i]);
  }
  dmx.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
  // panel
  panel.draw();
}
