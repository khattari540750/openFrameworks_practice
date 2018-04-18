//!
//! @file ofHatVec3d.h
//! @brief ofHatVec3d header file
//! @author HATTORI Kohei
//! @date 4/21/2016
//!

#ifndef __ofHatMath__ofHatVec3d__
#define __ofHatMath__ofHatVec3d__

#include "ofConstants.h"
#include "ofHatVec2d.h"
#include "ofHatVec4d.h"
#include "ofMain.h"
#include <cmath>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// class ofHatVec3d
////////////////////////////////////////////////////////////////////////////////
class ofHatVec3d {

public:
  static const int DIM = 3;
  double x;
  double y;
  double z;

public:
  // Construct a 3D vector
  ofHatVec3d();
  ofHatVec3d(double x, double y, double z = 0);
  explicit ofHatVec3d(double scalar);
  ofHatVec3d(const ofHatVec2d &vec);
  ofHatVec3d(const ofHatVec4d &vec);

  // Access components
  double *getPtr() { return (double *)&x; }
  const double *getPtr() const { return (const double *)&x; }
  double &operator[](int n) { return getPtr()[n]; }
  double operator[](int n) const { return getPtr()[n]; }
  void set(double x, double y, double z = 0);
  void set(const ofHatVec3d &vec);
  void set(double _scalar);

  // Comparison
  bool operator==(const ofHatVec3d &vec) const;
  bool operator!=(const ofHatVec3d &vec) const;
  bool match(const ofHatVec3d &vec, double tolerance = 0.00000001f) const;
  bool isAligned(const ofHatVec3d &vec, double tolerance = 0.00000001f) const;
  bool isAlignedRad(const ofHatVec3d &vec,
                    double tolerance = 0.00000001f) const;
  bool align(const ofHatVec3d &vec, double tolerance = 0.00000001f) const;
  bool alignRad(const ofHatVec3d &vec, double tolerance = 0.00000001f) const;

  // Operators
  ofHatVec3d operator+(const ofHatVec3d &pnt) const;
  ofHatVec3d operator+(const double f) const;
  ofHatVec3d &operator+=(const ofHatVec3d &pnt);
  ofHatVec3d &operator+=(const double f);
  ofHatVec3d operator-(const ofHatVec3d &vec) const;
  ofHatVec3d operator-(const double f) const;
  ofHatVec3d operator-() const;
  ofHatVec3d &operator-=(const ofHatVec3d &vec);
  ofHatVec3d &operator-=(const double f);
  ofHatVec3d operator*(const ofHatVec3d &vec) const;
  ofHatVec3d operator*(const double f) const;
  ofHatVec3d &operator*=(const ofHatVec3d &vec);
  ofHatVec3d &operator*=(const double f);
  ofHatVec3d operator/(const ofHatVec3d &vec) const;
  ofHatVec3d operator/(const double f) const;
  ofHatVec3d &operator/=(const ofHatVec3d &vec);
  ofHatVec3d &operator/=(const double f);
  friend ostream &operator<<(ostream &os, const ofHatVec3d &vec);
  friend istream &operator>>(istream &is, ofHatVec3d &vec);

  // Simple manipulations
  ofHatVec3d getScaled(const double length) const;
  ofHatVec3d &scale(const double length);
  ofHatVec3d getRotated(double angle, const ofHatVec3d &axis) const;
  ofHatVec3d getRotated(double ax, double ay, double az) const;
  ofHatVec3d getRotated(double angle, const ofHatVec3d &pivot,
                        const ofHatVec3d &axis) const;
  ofHatVec3d getRotatedRad(double angle, const ofHatVec3d &axis) const;
  ofHatVec3d getRotatedRad(double ax, double ay, double az) const;
  ofHatVec3d getRotatedRad(double angle, const ofHatVec3d &pivot,
                           const ofHatVec3d &axis) const;
  ofHatVec3d &rotate(double angle, const ofHatVec3d &axis);
  ofHatVec3d &rotate(double ax, double ay, double az);
  ofHatVec3d &rotate(double angle, const ofHatVec3d &pivot,
                     const ofHatVec3d &axis);
  ofHatVec3d &rotateRad(double angle, const ofHatVec3d &axis);
  ofHatVec3d &rotateRad(double ax, double ay, double az);
  ofHatVec3d &rotateRad(double angle, const ofHatVec3d &pivot,
                        const ofHatVec3d &axis);
  ofHatVec3d getMapped(const ofHatVec3d &origin, const ofHatVec3d &vx,
                       const ofHatVec3d &vy, const ofHatVec3d &vz) const;
  ofHatVec3d &map(const ofHatVec3d &origin, const ofHatVec3d &vx,
                  const ofHatVec3d &vy, const ofHatVec3d &vz);

  // Distance
  double distance(const ofHatVec3d &pnt) const;
  double squareDistance(const ofHatVec3d &pnt) const;

  // Interpolation
  ofHatVec3d getInterpolated(const ofHatVec3d &pnt, double p) const;
  ofHatVec3d &interpolate(const ofHatVec3d &pnt, double p);
  ofHatVec3d getMiddle(const ofHatVec3d &pnt) const;
  ofHatVec3d &middle(const ofHatVec3d &pnt);
  ofHatVec3d &average(const ofHatVec3d *points, int num);

  // Limit
  ofHatVec3d getNormalized() const;
  ofHatVec3d &normalize();
  ofHatVec3d getLimited(double max) const;
  ofHatVec3d &limit(double max);

  // Measurement
  double length() const;
  double lengthSquared() const;
  double angle(const ofHatVec3d &vec) const;
  double angleRad(const ofHatVec3d &vec) const;

  // Perpendicular
  ofHatVec3d getPerpendicular(const ofHatVec3d &vec) const;
  ofHatVec3d &perpendicular(const ofHatVec3d &vec);
  ofHatVec3d getCrossed(const ofHatVec3d &vec) const;
  ofHatVec3d &cross(const ofHatVec3d &vec);
  double dot(const ofHatVec3d &vec) const;

  // change to ofVec3f
  ofVec3f getOfVec3f() { return ofVec3f((float)x, (float)y, (float)z); }
};

////////////////////////////////////////////////////////////////////////////////
// Non-Member operators
////////////////////////////////////////////////////////////////////////////////
ofHatVec3d operator+(double f, const ofHatVec3d &vec);
ofHatVec3d operator-(double f, const ofHatVec3d &vec);
ofHatVec3d operator*(double f, const ofHatVec3d &vec);
ofHatVec3d operator/(double f, const ofHatVec3d &vec);

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Implementation
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//==============================================================================
// Construct a 3D vector
//==============================================================================
inline ofHatVec3d::ofHatVec3d(const ofHatVec2d &vec)
    : x(vec.x), y(vec.y), z(0) {}
inline ofHatVec3d::ofHatVec3d(const ofHatVec4d &vec)
    : x(vec.x), y(vec.y), z(vec.z) {}
inline ofHatVec3d::ofHatVec3d() : x(0), y(0), z(0) {}
inline ofHatVec3d::ofHatVec3d(double _all) : x(_all), y(_all), z(_all) {}
inline ofHatVec3d::ofHatVec3d(double _x, double _y, double _z)
    : x(_x), y(_y), z(_z) {}

//==============================================================================
// Access components
//==============================================================================
inline void ofHatVec3d::set(double _scalar) {
  x = _scalar;
  y = _scalar;
  z = _scalar;
}

inline void ofHatVec3d::set(double _x, double _y, double _z) {
  x = _x;
  y = _y;
  z = _z;
}

inline void ofHatVec3d::set(const ofHatVec3d &vec) {
  x = vec.x;
  y = vec.y;
  z = vec.z;
}

//==============================================================================
// Comparison
//==============================================================================
inline bool ofHatVec3d::operator==(const ofHatVec3d &vec) const {
  return (x == vec.x) && (y == vec.y) && (z == vec.z);
}

//------------------------------------------------------------------------------
inline bool ofHatVec3d::operator!=(const ofHatVec3d &vec) const {
  return (x != vec.x) || (y != vec.y) || (z != vec.z);
}

//------------------------------------------------------------------------------
inline bool ofHatVec3d::match(const ofHatVec3d &vec, double tolerance) const {
  return (fabs(x - vec.x) < tolerance) && (fabs(y - vec.y) < tolerance) &&
         (fabs(z - vec.z) < tolerance);
}

//------------------------------------------------------------------------------
inline bool ofHatVec3d::isAligned(const ofHatVec3d &vec,
                                  double tolerance) const {
  double angle = this->angle(vec);
  return angle < tolerance;
}

//------------------------------------------------------------------------------
inline bool ofHatVec3d::align(const ofHatVec3d &vec, double tolerance) const {
  return isAligned(vec, tolerance);
}

//------------------------------------------------------------------------------
inline bool ofHatVec3d::isAlignedRad(const ofHatVec3d &vec,
                                     double tolerance) const {
  double angle = this->angleRad(vec);
  return angle < tolerance;
}

//------------------------------------------------------------------------------
inline bool ofHatVec3d::alignRad(const ofHatVec3d &vec,
                                 double tolerance) const {
  return isAlignedRad(vec, tolerance);
}

//==============================================================================
// Operators
//==============================================================================
inline ostream &operator<<(ostream &os, const ofHatVec3d &vec) {
  os << vec.x << ", " << vec.y << ", " << vec.z;
  return os;
}

//------------------------------------------------------------------------------
inline istream &operator>>(istream &is, ofHatVec3d &vec) {
  is >> vec.x;
  is.ignore(2);
  is >> vec.y;
  is.ignore(2);
  is >> vec.z;
  return is;
}

//------------------------------------------------------------------------------
inline ofHatVec3d ofHatVec3d::operator+(const ofHatVec3d &pnt) const {
  return ofHatVec3d(x + pnt.x, y + pnt.y, z + pnt.z);
}

//------------------------------------------------------------------------------
inline ofHatVec3d &ofHatVec3d::operator+=(const ofHatVec3d &pnt) {
  x += pnt.x;
  y += pnt.y;
  z += pnt.z;
  return *this;
}

//------------------------------------------------------------------------------
inline ofHatVec3d ofHatVec3d::operator-(const ofHatVec3d &vec) const {
  return ofHatVec3d(x - vec.x, y - vec.y, z - vec.z);
}

//------------------------------------------------------------------------------
inline ofHatVec3d &ofHatVec3d::operator-=(const ofHatVec3d &vec) {
  x -= vec.x;
  y -= vec.y;
  z -= vec.z;
  return *this;
}

//------------------------------------------------------------------------------
inline ofHatVec3d ofHatVec3d::operator*(const ofHatVec3d &vec) const {
  return ofHatVec3d(x * vec.x, y * vec.y, z * vec.z);
}

//------------------------------------------------------------------------------
inline ofHatVec3d &ofHatVec3d::operator*=(const ofHatVec3d &vec) {
  x *= vec.x;
  y *= vec.y;
  z *= vec.z;
  return *this;
}

//------------------------------------------------------------------------------
inline ofHatVec3d ofHatVec3d::operator/(const ofHatVec3d &vec) const {
  return ofHatVec3d(vec.x != 0 ? x / vec.x : x, vec.y != 0 ? y / vec.y : y,
                    vec.z != 0 ? z / vec.z : z);
}

//------------------------------------------------------------------------------
inline ofHatVec3d &ofHatVec3d::operator/=(const ofHatVec3d &vec) {
  vec.x != 0 ? x /= vec.x : x;
  vec.y != 0 ? y /= vec.y : y;
  vec.z != 0 ? z /= vec.z : z;
  return *this;
}

//------------------------------------------------------------------------------
inline ofHatVec3d ofHatVec3d::operator-() const {
  return ofHatVec3d(-x, -y, -z);
}

//------------------------------------------------------------------------------
inline ofHatVec3d ofHatVec3d::operator+(const double f) const {
  return ofHatVec3d(x + f, y + f, z + f);
}

//------------------------------------------------------------------------------
inline ofHatVec3d &ofHatVec3d::operator+=(const double f) {
  x += f;
  y += f;
  z += f;
  return *this;
}

//------------------------------------------------------------------------------
inline ofHatVec3d ofHatVec3d::operator-(const double f) const {
  return ofHatVec3d(x - f, y - f, z - f);
}

//------------------------------------------------------------------------------
inline ofHatVec3d &ofHatVec3d::operator-=(const double f) {
  x -= f;
  y -= f;
  z -= f;
  return *this;
}

//------------------------------------------------------------------------------
inline ofHatVec3d ofHatVec3d::operator*(const double f) const {
  return ofHatVec3d(x * f, y * f, z * f);
}

//------------------------------------------------------------------------------
inline ofHatVec3d &ofHatVec3d::operator*=(const double f) {
  x *= f;
  y *= f;
  z *= f;
  return *this;
}

//------------------------------------------------------------------------------
inline ofHatVec3d ofHatVec3d::operator/(const double f) const {
  if (f == 0)
    return ofHatVec3d(x, y, z);

  return ofHatVec3d(x / f, y / f, z / f);
}

//------------------------------------------------------------------------------
inline ofHatVec3d &ofHatVec3d::operator/=(const double f) {
  if (f == 0)
    return *this;

  x /= f;
  y /= f;
  z /= f;
  return *this;
}

inline ofHatVec3d ofHatVec3d::getRotated(double angle, const ofHatVec3d &pivot,
                                         const ofHatVec3d &axis) const {
  ofHatVec3d ax = axis.getNormalized();
  double tx = x - pivot.x;
  double ty = y - pivot.y;
  double tz = z - pivot.z;

  double a = (double)(angle * DEG_TO_RAD);
  double sina = sin(a);
  double cosa = cos(a);
  double cosb = 1.0f - cosa;

  double xrot = tx * (ax.x * ax.x * cosb + cosa) +
                ty * (ax.x * ax.y * cosb - ax.z * sina) +
                tz * (ax.x * ax.z * cosb + ax.y * sina);
  double yrot = tx * (ax.y * ax.x * cosb + ax.z * sina) +
                ty * (ax.y * ax.y * cosb + cosa) +
                tz * (ax.y * ax.z * cosb - ax.x * sina);
  double zrot = tx * (ax.z * ax.x * cosb - ax.y * sina) +
                ty * (ax.z * ax.y * cosb + ax.x * sina) +
                tz * (ax.z * ax.z * cosb + cosa);

  return ofHatVec3d(xrot + pivot.x, yrot + pivot.y, zrot + pivot.z);
}

inline ofHatVec3d ofHatVec3d::getRotatedRad(double angle,
                                            const ofHatVec3d &pivot,
                                            const ofHatVec3d &axis) const {
  ofHatVec3d ax = axis.getNormalized();
  double tx = x - pivot.x;
  double ty = y - pivot.y;
  double tz = z - pivot.z;

  double a = angle;
  double sina = sin(a);
  double cosa = cos(a);
  double cosb = 1.0f - cosa;

  double xrot = tx * (ax.x * ax.x * cosb + cosa) +
                ty * (ax.x * ax.y * cosb - ax.z * sina) +
                tz * (ax.x * ax.z * cosb + ax.y * sina);
  double yrot = tx * (ax.y * ax.x * cosb + ax.z * sina) +
                ty * (ax.y * ax.y * cosb + cosa) +
                tz * (ax.y * ax.z * cosb - ax.x * sina);
  double zrot = tx * (ax.z * ax.x * cosb - ax.y * sina) +
                ty * (ax.z * ax.y * cosb + ax.x * sina) +
                tz * (ax.z * ax.z * cosb + cosa);

  return ofHatVec3d(xrot + pivot.x, yrot + pivot.y, zrot + pivot.z);
}

inline ofHatVec3d &ofHatVec3d::rotate(double angle, const ofHatVec3d &pivot,
                                      const ofHatVec3d &axis) {
  ofHatVec3d ax = axis.getNormalized();
  x -= pivot.x;
  y -= pivot.y;
  z -= pivot.z;

  double a = (double)(angle * DEG_TO_RAD);
  double sina = sin(a);
  double cosa = cos(a);
  double cosb = 1.0f - cosa;

  double xrot = x * (ax.x * ax.x * cosb + cosa) +
                y * (ax.x * ax.y * cosb - ax.z * sina) +
                z * (ax.x * ax.z * cosb + ax.y * sina);
  double yrot = x * (ax.y * ax.x * cosb + ax.z * sina) +
                y * (ax.y * ax.y * cosb + cosa) +
                z * (ax.y * ax.z * cosb - ax.x * sina);
  double zrot = x * (ax.z * ax.x * cosb - ax.y * sina) +
                y * (ax.z * ax.y * cosb + ax.x * sina) +
                z * (ax.z * ax.z * cosb + cosa);

  x = xrot + pivot.x;
  y = yrot + pivot.y;
  z = zrot + pivot.z;

  return *this;
}

inline ofHatVec3d &ofHatVec3d::rotateRad(double angle, const ofHatVec3d &pivot,
                                         const ofHatVec3d &axis) {
  ofHatVec3d ax = axis.getNormalized();
  x -= pivot.x;
  y -= pivot.y;
  z -= pivot.z;

  double a = angle;
  double sina = sin(a);
  double cosa = cos(a);
  double cosb = 1.0f - cosa;

  double xrot = x * (ax.x * ax.x * cosb + cosa) +
                y * (ax.x * ax.y * cosb - ax.z * sina) +
                z * (ax.x * ax.z * cosb + ax.y * sina);
  double yrot = x * (ax.y * ax.x * cosb + ax.z * sina) +
                y * (ax.y * ax.y * cosb + cosa) +
                z * (ax.y * ax.z * cosb - ax.x * sina);
  double zrot = x * (ax.z * ax.x * cosb - ax.y * sina) +
                y * (ax.z * ax.y * cosb + ax.x * sina) +
                z * (ax.z * ax.z * cosb + cosa);

  x = xrot + pivot.x;
  y = yrot + pivot.y;
  z = zrot + pivot.z;

  return *this;
}

inline ofHatVec3d &ofHatVec3d::perpendicular(const ofHatVec3d &vec) {
  double crossX = y * vec.z - z * vec.y;
  double crossY = z * vec.x - x * vec.z;
  double crossZ = x * vec.y - y * vec.x;

  double length =
      (double)sqrt(crossX * crossX + crossY * crossY + crossZ * crossZ);

  if (length > 0) {
    x = crossX / length;
    y = crossY / length;
    z = crossZ / length;
  } else {
    x = 0.f;
    y = 0.f;
    z = 0.f;
  }

  return *this;
}

// Length
//
//
inline double ofHatVec3d::length() const {
  return (double)sqrt(x * x + y * y + z * z);
}

inline double ofHatVec3d::lengthSquared() const {
  return (double)(x * x + y * y + z * z);
}

//
// Angle (deg) between two vectors.
// This is an unsigned relative angle from 0 to 180.
// http://www.euclideanspace.com/maths/algebra/vectors/angleBetween/index.htm
//
inline double ofHatVec3d::angle(const ofHatVec3d &vec) const {
  ofHatVec3d n1 = this->getNormalized();
  ofHatVec3d n2 = vec.getNormalized();
  return (double)(acos(n1.dot(n2)) * RAD_TO_DEG);
}

inline double ofHatVec3d::angleRad(const ofHatVec3d &vec) const {
  ofHatVec3d n1 = this->getNormalized();
  ofHatVec3d n2 = vec.getNormalized();
  return (double)acos(n1.dot(n2));
}

//==============================================================================
// Calculations
//==============================================================================
inline double ofHatVec3d::dot(const ofHatVec3d &vec) const {
  return x * vec.x + y * vec.y + z * vec.z;
}

//==============================================================================
// Non-Member operators
//==============================================================================
inline ofHatVec3d operator+(double f, const ofHatVec3d &vec) {
  return ofHatVec3d(f + vec.x, f + vec.y, f + vec.z);
}

//------------------------------------------------------------------------------
inline ofHatVec3d operator-(double f, const ofHatVec3d &vec) {
  return ofHatVec3d(f - vec.x, f - vec.y, f - vec.z);
}

//------------------------------------------------------------------------------
inline ofHatVec3d operator*(double f, const ofHatVec3d &vec) {
  return ofHatVec3d(f * vec.x, f * vec.y, f * vec.z);
}

//------------------------------------------------------------------------------
inline ofHatVec3d operator/(double f, const ofHatVec3d &vec) {
  return ofHatVec3d(f / vec.x, f / vec.y, f / vec.z);
}

#endif