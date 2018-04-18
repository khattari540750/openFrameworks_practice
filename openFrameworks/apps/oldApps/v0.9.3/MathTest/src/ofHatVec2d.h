//!
//! @file ofHatVec2d.h
//! @brief ofHatVec2d header file
//! @author HATTORI Kohei
//! @date 4/22/2016
//!

#ifndef __ofHatMath__ofHatVec2d__
#define __ofHatMath__ofHatVec2d__

class ofHatVec3d;
class ofHatVec4d;
#include "ofConstants.h"
#include "ofMain.h"

////////////////////////////////////////////////////////////////////////////////
// class ofHatVec2d
////////////////////////////////////////////////////////////////////////////////
class ofHatVec2d {

public:
  static const int DIM = 2;
  double x;
  double y;

public:
  // Construct a 2D vector
  ofHatVec2d();
  explicit ofHatVec2d(double scalar);
  ofHatVec2d(double x, double y);
  ofHatVec2d(const ofHatVec3d &vec);
  ofHatVec2d(const ofHatVec4d &vec);

  // Access components
  double *getPtr() { return (double *)&x; }
  const double *getPtr() const { return (const double *)&x; }
  double &operator[](int n) { return getPtr()[n]; }
  double operator[](int n) const { return getPtr()[n]; }
  void set(double x, double y);
  void set(const ofHatVec2d &vec);
  void set(double scalar);

  // Comparison
  bool operator==(const ofHatVec2d &vec) const;
  bool operator!=(const ofHatVec2d &vec) const;
  bool match(const ofHatVec2d &vec, double tolerance = 0.00000001f) const;
  bool isAligned(const ofHatVec2d &vec, double tolerance = 0.00000001f) const;
  bool isAlignedRad(const ofHatVec2d &vec,
                    double tolerance = 0.00000001f) const;
  bool align(const ofHatVec2d &vec, double tolerance = 0.00000001f) const;
  bool alignRad(const ofHatVec2d &vec, double tolerance = 0.00000001f) const;

  // Operators
  ofHatVec2d operator+(const ofHatVec2d &vec) const;
  ofHatVec2d operator+(const double f) const;
  ofHatVec2d &operator+=(const ofHatVec2d &vec);
  ofHatVec2d &operator+=(const double f);
  ofHatVec2d operator-(const ofHatVec2d &vec) const;
  ofHatVec2d operator-(const double f) const;
  ofHatVec2d operator-() const;
  ofHatVec2d &operator-=(const ofHatVec2d &vec);
  ofHatVec2d &operator-=(const double f);
  ofHatVec2d operator*(const ofHatVec2d &vec) const;
  ofHatVec2d operator*(const double f) const;
  ofHatVec2d &operator*=(const ofHatVec2d &vec);
  ofHatVec2d &operator*=(const double f);
  ofHatVec2d operator/(const ofHatVec2d &vec) const;
  ofHatVec2d operator/(const double f) const;
  ofHatVec2d &operator/=(const ofHatVec2d &vec);
  ofHatVec2d &operator/=(const double f);
  friend ostream &operator<<(ostream &os, const ofHatVec2d &vec);
  friend istream &operator>>(istream &is, const ofHatVec2d &vec);

  // Simple manipulations
  ofHatVec2d getScaled(const double length) const;
  ofHatVec2d &scale(const double length);
  ofHatVec2d getRotated(double angle) const;
  ofHatVec2d getRotated(double angle, const ofHatVec2d &pivot) const;
  ofHatVec2d getRotatedRad(double angle) const;
  ofHatVec2d getRotatedRad(double angle, const ofHatVec2d &pivot) const;
  ofHatVec2d &rotate(double angle);
  ofHatVec2d &rotate(double angle, const ofHatVec2d &pivot);
  ofHatVec2d &rotateRad(double angle);
  ofHatVec2d &rotateRad(double angle, const ofHatVec2d &pivot);
  ofHatVec2d getMapped(const ofHatVec2d &origin, const ofHatVec2d &vx,
                       const ofHatVec2d &vy) const;
  ofHatVec2d &map(const ofHatVec2d &origin, const ofHatVec2d &vx,
                  const ofHatVec2d &vy);

  // Distance
  double distance(const ofHatVec2d &pnt) const;
  double squareDistance(const ofHatVec2d &pnt) const;
  ofHatVec2d getInterpolated(const ofHatVec2d &pnt, double p) const;
  ofHatVec2d &interpolate(const ofHatVec2d &pnt, double p);
  ofHatVec2d getMiddle(const ofHatVec2d &pnt) const;
  ofHatVec2d &middle(const ofHatVec2d &pnt);
  ofHatVec2d &average(const ofHatVec2d *points, std::size_t num);

  // Limit
  ofHatVec2d getNormalized() const;
  ofHatVec2d &normalize();
  ofHatVec2d getLimited(double max) const;
  ofHatVec2d &limit(double max);

  // Measurement
  double length() const;
  double lengthSquared() const;
  double angle(const ofHatVec2d &vec) const;
  double angleRad(const ofHatVec2d &vec) const;

  // Perpendicular
  ofHatVec2d getPerpendicular() const;
  ofHatVec2d &perpendicular();
  double dot(const ofHatVec2d &vec) const;

  // change to ofVec2f
  ofVec2f getOfVec2f() { return ofVec2f((float)x, (float)y); }
};

////////////////////////////////////////////////////////////////////////////////
// Non-Member operators
////////////////////////////////////////////////////////////////////////////////
ofHatVec2d operator+(double f, const ofHatVec2d &vec);
ofHatVec2d operator-(double f, const ofHatVec2d &vec);
ofHatVec2d operator*(double f, const ofHatVec2d &vec);
ofHatVec2d operator/(double f, const ofHatVec2d &vec);

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Implementation
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//==============================================================================
// Construct a 2D vector
//==============================================================================
inline ofHatVec2d::ofHatVec2d() : x(0), y(0) {}

inline ofHatVec2d::ofHatVec2d(double _scalar) : x(_scalar), y(_scalar) {}

inline ofHatVec2d::ofHatVec2d(double _x, double _y) : x(_x), y(_y) {}

//==============================================================================
// Access components
//==============================================================================
inline void ofHatVec2d::set(double _scalar) {
  x = _scalar;
  y = _scalar;
}

inline void ofHatVec2d::set(double _x, double _y) {
  x = _x;
  y = _y;
}

inline void ofHatVec2d::set(const ofHatVec2d &vec) {
  x = vec.x;
  y = vec.y;
}

//==============================================================================
// Comparison
//==============================================================================
inline bool ofHatVec2d::operator==(const ofHatVec2d &vec) const {
  return (x == vec.x) && (y == vec.y);
}

//------------------------------------------------------------------------------
inline bool ofHatVec2d::operator!=(const ofHatVec2d &vec) const {
  return (x != vec.x) || (y != vec.y);
}

//------------------------------------------------------------------------------
inline bool ofHatVec2d::match(const ofHatVec2d &vec, double tolerance) const {
  return (fabs(x - vec.x) < tolerance) && (fabs(y - vec.y) < tolerance);
}

//------------------------------------------------------------------------------
inline bool ofHatVec2d::isAligned(const ofHatVec2d &vec,
                                  double tolerance) const {
  return fabs(this->angle(vec)) < tolerance;
}

//------------------------------------------------------------------------------
inline bool ofHatVec2d::align(const ofHatVec2d &vec, double tolerance) const {
  return isAligned(vec, tolerance);
}

//------------------------------------------------------------------------------
inline bool ofHatVec2d::isAlignedRad(const ofHatVec2d &vec,
                                     double tolerance) const {
  return fabs(this->angleRad(vec)) < tolerance;
}

//------------------------------------------------------------------------------
inline bool ofHatVec2d::alignRad(const ofHatVec2d &vec,
                                 double tolerance) const {
  return isAlignedRad(vec, tolerance);
}

//==============================================================================
// Operators
//==============================================================================
inline ofHatVec2d ofHatVec2d::operator+(const ofHatVec2d &vec) const {
  return ofHatVec2d(x + vec.x, y + vec.y);
}

inline ofHatVec2d ofHatVec2d::operator+(const double f) const {
  return ofHatVec2d(x + f, y + f);
}

//------------------------------------------------------------------------------
inline ofHatVec2d &ofHatVec2d::operator+=(const ofHatVec2d &vec) {
  x += vec.x;
  y += vec.y;
  return *this;
}

inline ofHatVec2d &ofHatVec2d::operator+=(const double f) {
  x += f;
  y += f;
  return *this;
}

//------------------------------------------------------------------------------
inline ofHatVec2d ofHatVec2d::operator-(const ofHatVec2d &vec) const {
  return ofHatVec2d(x - vec.x, y - vec.y);
}

inline ofHatVec2d ofHatVec2d::operator-(const double f) const {
  return ofHatVec2d(x - f, y - f);
}

inline ofHatVec2d ofHatVec2d::operator-() const { return ofHatVec2d(-x, -y); }

//------------------------------------------------------------------------------
inline ofHatVec2d &ofHatVec2d::operator-=(const ofHatVec2d &vec) {
  x -= vec.x;
  y -= vec.y;
  return *this;
}

inline ofHatVec2d &ofHatVec2d::operator-=(const double f) {
  x -= f;
  y -= f;
  return *this;
}

//------------------------------------------------------------------------------
inline ofHatVec2d ofHatVec2d::operator*(const ofHatVec2d &vec) const {
  return ofHatVec2d(x * vec.x, y * vec.y);
}

inline ofHatVec2d ofHatVec2d::operator*(const double f) const {
  return ofHatVec2d(x * f, y * f);
}

//------------------------------------------------------------------------------
inline ofHatVec2d &ofHatVec2d::operator*=(const ofHatVec2d &vec) {
  x *= vec.x;
  y *= vec.y;
  return *this;
}

inline ofHatVec2d &ofHatVec2d::operator*=(const double f) {
  x *= f;
  y *= f;
  return *this;
}

//------------------------------------------------------------------------------
inline ofHatVec2d ofHatVec2d::operator/(const ofHatVec2d &vec) const {
  return ofHatVec2d(vec.x != 0 ? x / vec.x : x, vec.y != 0 ? y / vec.y : y);
}

inline ofHatVec2d ofHatVec2d::operator/(const double f) const {
  if (f == 0)
    return ofHatVec2d(x, y);

  return ofHatVec2d(x / f, y / f);
}

//------------------------------------------------------------------------------
inline ofHatVec2d &ofHatVec2d::operator/=(const ofHatVec2d &vec) {
  vec.x != 0 ? x /= vec.x : x;
  vec.y != 0 ? y /= vec.y : y;
  return *this;
}

inline ofHatVec2d &ofHatVec2d::operator/=(const double f) {
  if (f == 0)
    return *this;

  x /= f;
  y /= f;
  return *this;
}

//------------------------------------------------------------------------------
inline ostream &operator<<(ostream &os, const ofHatVec2d &vec) {
  os << vec.x << ", " << vec.y;
  return os;
}

//------------------------------------------------------------------------------
inline istream &operator>>(istream &is, ofHatVec2d &vec) {
  is >> vec.x;
  is.ignore(2);
  is >> vec.y;
  return is;
}

//==============================================================================
// Measurement
//==============================================================================
inline double ofHatVec2d::length() const { return (double)sqrt(x * x + y * y); }

//------------------------------------------------------------------------------
inline double ofHatVec2d::lengthSquared() const {
  return (double)(x * x + y * y);
}

//------------------------------------------------------------------------------
inline double ofHatVec2d::angle(const ofHatVec2d &vec) const {
  return (double)(atan2(x * vec.y - y * vec.x, x * vec.x + y * vec.y) *
                  RAD_TO_DEG);
}

//------------------------------------------------------------------------------
inline double ofHatVec2d::angleRad(const ofHatVec2d &vec) const {
  return atan2(x * vec.y - y * vec.x, x * vec.x + y * vec.y);
}

//==============================================================================
// Perpendicular
//==============================================================================
inline double ofHatVec2d::dot(const ofHatVec2d &vec) const {
  return x * vec.x + y * vec.y;
}

//==============================================================================
// Non-Member operators
//==============================================================================
inline ofHatVec2d operator+(double f, const ofHatVec2d &vec) {
  return ofHatVec2d(f + vec.x, f + vec.y);
}

//------------------------------------------------------------------------------
inline ofHatVec2d operator-(double f, const ofHatVec2d &vec) {
  return ofHatVec2d(f - vec.x, f - vec.y);
}

//------------------------------------------------------------------------------
inline ofHatVec2d operator*(double f, const ofHatVec2d &vec) {
  return ofHatVec2d(f * vec.x, f * vec.y);
}

//------------------------------------------------------------------------------
inline ofHatVec2d operator/(double f, const ofHatVec2d &vec) {
  return ofHatVec2d(f / vec.x, f / vec.y);
}

#endif