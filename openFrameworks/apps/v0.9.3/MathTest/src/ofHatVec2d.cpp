//!
//! @file ofHatVec2d.cpp
//! @brief ofHatVec2d source file
//! @author HATTORI Kohei
//! @date 4/22/2016
//!

#include "ofHatVec2d.h"
#include "ofHatVec3d.h"
#include "ofHatVec4d.h"

//==============================================================================
// Construct a 2D vector
//==============================================================================
inline ofHatVec2d::ofHatVec2d(const ofHatVec3d &vec) {
  x = vec.x;
  y = vec.y;
}

inline ofHatVec2d::ofHatVec2d(const ofHatVec4d &vec) {
  x = vec.x;
  y = vec.y;
}