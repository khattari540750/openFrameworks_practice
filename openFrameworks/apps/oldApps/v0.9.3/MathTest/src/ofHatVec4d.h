//!
//! @file ofHatVec4d.h
//! @brief ofHatVec4d header file
//! @author HATTORI Kohei
//! @date 4/21/2016
//!

#ifndef __ofHatMath__ofHatVec4d__
#define __ofHatMath__ofHatVec4d__

class ofHatVec2d;
class ofHatVec3d;
#include "ofConstants.h"
#include "ofMain.h"

////////////////////////////////////////////////////////////////////////////////
// class ofHatVec4d
////////////////////////////////////////////////////////////////////////////////
class ofHatVec4d {

public:
  static const int DIM = 4;
  double x;
  double y;
  double z;
  double w;

public:
  // Construct a 4D vector
  ofHatVec4d();
  explicit ofHatVec4d(double _scalar);
  ofHatVec4d(double _x, double _y, double _z, double _w);
  ofHatVec4d(const ofHatVec2d &vec);
  ofHatVec4d(const ofHatVec3d &vec);

  // Access components
  double *getPtr() { return (double *)&x; }
  const double *getPtr() const { return (const double *)&x; }
  double &operator[](int n) { return getPtr()[n]; }
  double operator[](int n) const { return getPtr()[n]; }
  void set(double _scalar);
  void set(double _x, double _y, double _z, double _w);
  void set(const ofHatVec4d &vec);

  // Comparison
  bool operator==(const ofHatVec4d &vec) const;
  bool operator!=(const ofHatVec4d &vec) const;
  bool match(const ofHatVec4d &vec, double tolerance = 0.00000001f) const;

  // Operators
  ofHatVec4d operator+(const ofHatVec4d &vec) const;
  ofHatVec4d operator+(const double f) const;
  ofHatVec4d &operator+=(const ofHatVec4d &vec);
  ofHatVec4d &operator+=(const double f);
  ofHatVec4d operator-(const double f) const;
  ofHatVec4d operator-(const ofHatVec4d &vec) const;
  ofHatVec4d operator-() const;
  ofHatVec4d &operator-=(const double f);
  ofHatVec4d &operator-=(const ofHatVec4d &vec);
  ofHatVec4d operator*(const ofHatVec4d &vec) const;
  ofHatVec4d operator*(const double f) const;
  ofHatVec4d &operator*=(const ofHatVec4d &vec);
  ofHatVec4d &operator*=(const double f);
  ofHatVec4d operator/(const ofHatVec4d &vec) const;
  ofHatVec4d operator/(const double f) const;
  ofHatVec4d &operator/=(const ofHatVec4d &vec);
  ofHatVec4d &operator/=(const double f);
  friend ostream &operator<<(ostream &os, const ofHatVec4d &vec);
  friend istream &operator>>(istream &is, const ofHatVec4d &vec);

  // Simple manipulations
  ofHatVec4d getScaled(const double length) const;
  ofHatVec4d &scale(const double length);

  // Distance
  double distance(const ofHatVec4d &pnt) const;
  double squareDistance(const ofHatVec4d &pnt) const;

  // Interpolation
  ofHatVec4d getInterpolated(const ofHatVec4d &pnt, double p) const;
  ofHatVec4d &interpolate(const ofHatVec4d &pnt, double p);
  ofHatVec4d getMiddle(const ofHatVec4d &pnt) const;
  ofHatVec4d &middle(const ofHatVec4d &pnt);
  ofHatVec4d &average(const ofHatVec4d *points, int num);

  // Limit
  ofHatVec4d getNormalized() const;
  ofHatVec4d &normalize();
  ofHatVec4d getLimited(double max) const;
  ofHatVec4d &limit(double max);

  // Measurement
  double length() const;
  double lengthSquared() const;

  // Calculations
  double dot(const ofHatVec4d &vec) const;

  // change ofVec4f
  ofVec4f getOfVec4f() {
    return ofVec4f((float)x, (float)y, (float)z, (float)w);
  }
};

////////////////////////////////////////////////////////////////////////////////
// Non-Member operators
////////////////////////////////////////////////////////////////////////////////
ofHatVec4d operator+(double f, const ofHatVec4d &vec);
ofHatVec4d operator-(double f, const ofHatVec4d &vec);
ofHatVec4d operator*(double f, const ofHatVec4d &vec);
ofHatVec4d operator/(double f, const ofHatVec4d &vec);

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Implementation
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//==============================================================================
// Construct a 4D vector
//==============================================================================
inline ofHatVec4d::ofHatVec4d() : x(0), y(0), z(0), w(0) {}

inline ofHatVec4d::ofHatVec4d(double _s) : x(_s), y(_s), z(_s), w(_s) {}

inline ofHatVec4d::ofHatVec4d(double _x, double _y, double _z, double _w)
    : x(_x), y(_y), z(_z), w(_w) {}

//==============================================================================
// Access components
//==============================================================================
inline void ofHatVec4d::set(double _scalar) {
  x = _scalar;
  y = _scalar;
  z = _scalar;
  w = _scalar;
}

inline void ofHatVec4d::set(double _x, double _y, double _z, double _w) {
  x = _x;
  y = _y;
  z = _z;
  w = _w;
}

inline void ofHatVec4d::set(const ofHatVec4d &vec) {
  x = vec.x;
  y = vec.y;
  z = vec.z;
  w = vec.w;
}

//==============================================================================
// Comparison
//==============================================================================
inline bool ofHatVec4d::operator==(const ofHatVec4d &vec) const {
  return (x == vec.x) && (y == vec.y) && (z == vec.z) && (w == vec.w);
}

//------------------------------------------------------------------------------
inline bool ofHatVec4d::operator!=(const ofHatVec4d &vec) const {
  return (x != vec.x) || (y != vec.y) || (z != vec.z) || (w != vec.w);
}

//------------------------------------------------------------------------------
inline bool ofHatVec4d::match(const ofHatVec4d &vec, double tolerance) const {
  return (fabs(x - vec.x) < tolerance) && (fabs(y - vec.y) < tolerance) &&
         (fabs(z - vec.z) < tolerance) && (fabs(w - vec.w) < tolerance);
}

//==============================================================================
// Operators
//==============================================================================
inline ofHatVec4d ofHatVec4d::operator+(const ofHatVec4d &vec) const {
  return ofHatVec4d(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
}

//------------------------------------------------------------------------------
inline ofHatVec4d &ofHatVec4d::operator+=(const ofHatVec4d &vec) {
  x += vec.x;
  y += vec.y;
  z += vec.z;
  w += vec.w;
  return *this;
}

//------------------------------------------------------------------------------
inline ofHatVec4d ofHatVec4d::operator-(const double f) const {
  return ofHatVec4d(x - f, y - f, z - f, w - f);
}

//------------------------------------------------------------------------------
inline ofHatVec4d &ofHatVec4d::operator-=(const double f) {
  x -= f;
  y -= f;
  z -= f;
  w -= f;
  return *this;
}

//------------------------------------------------------------------------------
inline ofHatVec4d ofHatVec4d::operator-(const ofHatVec4d &vec) const {
  return ofHatVec4d(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
}

//------------------------------------------------------------------------------
inline ofHatVec4d &ofHatVec4d::operator-=(const ofHatVec4d &vec) {
  x -= vec.x;
  y -= vec.y;
  z -= vec.z;
  w -= vec.w;
  return *this;
}

//------------------------------------------------------------------------------
inline ofHatVec4d ofHatVec4d::operator+(const double f) const {
  return ofHatVec4d(x + f, y + f, z + f, w + f);
}

//------------------------------------------------------------------------------
inline ofHatVec4d &ofHatVec4d::operator+=(const double f) {
  x += f;
  y += f;
  z += f;
  w += f;
  return *this;
}

//------------------------------------------------------------------------------
inline ofHatVec4d ofHatVec4d::operator-() const {
  return ofHatVec4d(-x, -y, -z, -w);
}

//------------------------------------------------------------------------------
inline ofHatVec4d ofHatVec4d::operator*(const ofHatVec4d &vec) const {
  return ofHatVec4d(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
}

//------------------------------------------------------------------------------
inline ofHatVec4d &ofHatVec4d::operator*=(const ofHatVec4d &vec) {
  x *= vec.x;
  y *= vec.y;
  z *= vec.z;
  w *= vec.w;
  return *this;
}

//------------------------------------------------------------------------------
inline ofHatVec4d ofHatVec4d::operator*(const double f) const {
  return ofHatVec4d(x * f, y * f, z * f, w * f);
}

//------------------------------------------------------------------------------
inline ofHatVec4d &ofHatVec4d::operator*=(const double f) {
  x *= f;
  y *= f;
  z *= f;
  w *= f;
  return *this;
}

//------------------------------------------------------------------------------
inline ofHatVec4d ofHatVec4d::operator/(const ofHatVec4d &vec) const {
  return ofHatVec4d(vec.x != 0 ? x / vec.x : x, vec.y != 0 ? y / vec.y : y,
                    vec.z != 0 ? z / vec.z : z, vec.w != 0 ? w / vec.w : w);
}

//------------------------------------------------------------------------------
inline ofHatVec4d &ofHatVec4d::operator/=(const ofHatVec4d &vec) {
  vec.x != 0 ? x /= vec.x : x;
  vec.y != 0 ? y /= vec.y : y;
  vec.z != 0 ? z /= vec.z : z;
  vec.w != 0 ? w /= vec.w : w;
  return *this;
}

//------------------------------------------------------------------------------
inline ofHatVec4d ofHatVec4d::operator/(const double f) const {
  if (f == 0)
    return ofHatVec4d(x, y, z, w);

  return ofHatVec4d(x / f, y / f, z / f, w / f);
}

//------------------------------------------------------------------------------
inline ofHatVec4d &ofHatVec4d::operator/=(const double f) {
  if (f == 0)
    return *this;

  x /= f;
  y /= f;
  z /= f;
  w /= f;
  return *this;
}

//------------------------------------------------------------------------------
inline ostream &operator<<(ostream &os, const ofHatVec4d &vec) {
  os << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w;
  return os;
}

//------------------------------------------------------------------------------
inline istream &operator>>(istream &is, ofHatVec4d &vec) {
  is >> vec.x;
  is.ignore(2);
  is >> vec.y;
  is.ignore(2);
  is >> vec.z;
  is.ignore(2);
  is >> vec.w;
  return is;
}

//==============================================================================
// Limit
//==============================================================================
inline ofHatVec4d &ofHatVec4d::limit(double max) {
  double lengthSquared = (x * x + y * y + z * z + w * w);
  if (lengthSquared > max * max && lengthSquared > 0) {
    double ratio = max / (double)sqrt(lengthSquared);
    x *= ratio;
    y *= ratio;
    z *= ratio;
    w *= ratio;
  }
  return *this;
}

//==============================================================================
// Measurement
//==============================================================================
inline double ofHatVec4d::length() const {
  return (double)sqrt(x * x + y * y + z * z + w * w);
}

//------------------------------------------------------------------------------
inline double ofHatVec4d::lengthSquared() const {
  return (double)(x * x + y * y + z * z + w * w);
}

//==============================================================================
// Calculations
//==============================================================================
inline double ofHatVec4d::dot(const ofHatVec4d &vec) const {
  return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
}

//==============================================================================
// Non-Member operators
//==============================================================================
inline ofHatVec4d operator+(double f, const ofHatVec4d &vec) {
  return ofHatVec4d(f + vec.x, f + vec.y, f + vec.z, f + vec.w);
}

//------------------------------------------------------------------------------
inline ofHatVec4d operator-(double f, const ofHatVec4d &vec) {
  return ofHatVec4d(f - vec.x, f - vec.y, f - vec.z, f - vec.w);
}

//------------------------------------------------------------------------------
inline ofHatVec4d operator*(double f, const ofHatVec4d &vec) {
  return ofHatVec4d(f * vec.x, f * vec.y, f * vec.z, f * vec.w);
}

//------------------------------------------------------------------------------
inline ofHatVec4d operator/(double f, const ofHatVec4d &vec) {
  return ofHatVec4d(f / vec.x, f / vec.y, f / vec.z, f / vec.w);
}

#endif