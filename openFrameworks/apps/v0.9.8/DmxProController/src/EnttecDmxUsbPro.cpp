//
//  EnttecDmxUsbPro.cpp
//  DmxProController
//

#include "EnttecDmxUsbPro.hpp"

//==============================================================================
// constructor destructor
//==============================================================================
//!
//! @fn EnttecDmxUsbPro::EnttecDmxUsbPro
//! @brief constructor
//!
EnttecDmxUsbPro::EnttecDmxUsbPro() { updateEnabled = true; }

//------------------------------------------------------------------------------
//!
//! @fn EnttecDmxUsbPro::~EnttecDmxUsbPro
//! @brief destructor
//!
EnttecDmxUsbPro::~EnttecDmxUsbPro() {
  usbPro.disconnect();
  ofLogNotice("EnttecDmxUsbPro::~EnttecDmxUsbPro") << "end of communication "
                                                   << devicePath;
  usbPro.clear();
}

//==============================================================================
// basic
//==============================================================================
//!
//! @fn EnttecDmxUsbPro::addUniverse
//! @brief
//!
void EnttecDmxUsbPro::addUniverse(int universeNum,
                                             vector<unsigned int> *dmxDataPtr,
                                             int channelTotal) {
  this->universeNum = universeNum;
  this->dmxDataPtr = dmxDataPtr;
  this->channelTotal = channelTotal;
}

//------------------------------------------------------------------------------
//!
//! @fn EnttecDmxUsbPro::setup
//! @brief
//!
void EnttecDmxUsbPro::setup(string devicePath) {
  this->devicePath = devicePath;
  ofLogNotice("EnttecDmxUsbPro::setup") << "try connect " << this->devicePath;
  usbPro.connect(this->devicePath, channelTotal);
}

//------------------------------------------------------------------------------
//!
//! @fn EnttecDmxUsbPro::update
//! @brief
//!
void EnttecDmxUsbPro::update() {
  if (usbPro.isConnected() && updateEnabled) {
    for (int i = 0; i < dmxDataPtr->size(); i++) {
      usbPro.setLevel(i + 1, dmxDataPtr->at(i));
    }
    usbPro.update();
  }
}

//==============================================================================
// basic
//==============================================================================
//!
//! @fn EnttecDmxUsbPro::enableCommunicate
//! @brief
//!
void EnttecDmxUsbPro::enableCommunicate() {
  updateEnabled = true;
  ofLogVerbose("EnttecDmxUsbPro::enableCommunicate") << "updateEnabled is true";
}

//------------------------------------------------------------------------------
//!
//! @fn EnttecDmxUsbPro::disableCommunicate
//! @brief
//!
void EnttecDmxUsbPro::disableCommunicate() {
  updateEnabled = false;
  ofLogVerbose("EnttecDmxUsbPro::disableCommunicate")
      << "updateEnabled is false";
}

//------------------------------------------------------------------------------
//!
//! @fn EnttecDmxUsbPro::getDmxDataPtr
//! @brief
//!
vector<unsigned int> *EnttecDmxUsbPro::getDmxDataPtr() {
  return dmxDataPtr;
}