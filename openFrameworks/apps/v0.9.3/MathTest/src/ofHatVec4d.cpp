//!
//! @file ofHatVec4d.cpp
//! @brief ofHatVec4d source file
//! @author HATTORI Kohei
//! @date 4/21/2016
//!

#include "ofHatVec2d.h"
#include "ofHatVec3d.h"
#include "ofHatVec4d.h"

//==============================================================================
// Construct a 4D vector
//==============================================================================
inline ofHatVec4d::ofHatVec4d(const ofHatVec3d &vec) {
  x = vec.x;
  y = vec.y;
  z = vec.z;
  w = 0;
}

inline ofHatVec4d::ofHatVec4d(const ofHatVec2d &vec) {
  x = vec.x;
  y = vec.y;
  z = 0;
  w = 0;
}