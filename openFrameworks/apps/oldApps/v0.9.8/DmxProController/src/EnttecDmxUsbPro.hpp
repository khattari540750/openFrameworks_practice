//
//  EnttecDmxUsbPro.hpp
//  DmxProController
//

#ifndef EnttecDmxUsbPro_hpp
#define EnttecDmxUsbPro_hpp

#include "ofMain.h"
#include "ofxDmx.h"

////////////////////////////////////////////////////////////////////////////////
// EnttecDmxUsbPro class
////////////////////////////////////////////////////////////////////////////////
class EnttecDmxUsbPro {
public:
  // constructor destructor
  EnttecDmxUsbPro();
  ~EnttecDmxUsbPro();

  void addUniverse(int universeNum, vector<unsigned int> *dmxDataPtr,
                   int channelTotal = 512);
  void setup(string devicePath);
  void update();

  // status functions
  void enableCommunicate();
  void disableCommunicate();

  // get
  vector<unsigned int> *getDmxDataPtr();

private:
  ofxDmx usbPro;
  string devicePath;
  int universeNum;
  int channelTotal;
  bool updateEnabled;
  vector<unsigned int> *dmxDataPtr;
};

#endif
