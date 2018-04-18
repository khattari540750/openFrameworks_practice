//!
//! @file ofHatQuaternion.h
//! @brief ofHatQuaternion header file
//! @author HATTORI Kohei
//! @date 4/21/2016
//!

#ifndef __ofHatMath__ofHatQuaternion__
#define __ofHatMath__ofHatQuaternion__

#include "ofConstants.h"
#include "ofHatVec3d.h"
#include "ofHatVec4d.h"
#include <cmath>

#if (_MSC_VER)
#pragma warning(disable : 4244)
#endif

class ofHatMatrix4x4;

class ofHatQuaternion {

public:
  ofHatVec4d _v;

public:
  // Constructor
  inline ofHatQuaternion();
  inline ofHatQuaternion(double x, double y, double z, double w);
  inline ofHatQuaternion(const ofHatVec4d &v);
  inline ofHatQuaternion(double angle, const ofHatVec3d &axis);
  inline ofHatQuaternion(double angle1, const ofHatVec3d &axis1, double angle2,
                         const ofHatVec3d &axis2, double angle3,
                         const ofHatVec3d &axis3);

  // Setters
  inline void set(double x, double y, double z, double w);
  inline void set(const ofHatVec4d &v);
  void set(const ofHatMatrix4x4 &matrix);

  // Getters
  inline double &operator[](int i);
  inline double operator[](int i) const;
  void get(ofHatMatrix4x4 &matrix) const;
  inline double &x();
  inline double &y();
  inline double &z();
  inline double &w();
  inline double x() const;
  inline double y() const;
  inline double z() const;
  inline double w() const;
  inline ofHatVec4d asVec4() const;
  inline ofHatVec3d asVec3() const;

  // Functions
  inline bool zeroRotation() const;
  inline double length() const;
  inline double length2() const;
  inline ofHatQuaternion conj() const;
  inline const ofHatQuaternion inverse() const;
  void makeRotate(double angle, double x, double y, double z);
  void makeRotate(double angle, const ofHatVec3d &vec);
  void makeRotate(double angle1, const ofHatVec3d &axis1, double angle2,
                  const ofHatVec3d &axis2, double angle3,
                  const ofHatVec3d &axis3);
  void makeRotate(const ofHatVec3d &vec1, const ofHatVec3d &vec2);
  void makeRotate_original(const ofHatVec3d &vec1, const ofHatVec3d &vec2);
  void getRotate(double &angle, double &x, double &y, double &z) const;
  void getRotate(double &angle, ofHatVec3d &vec) const;
  ofHatVec3d getEuler() const;
  void slerp(double t, const ofHatQuaternion &from, const ofHatQuaternion &to);
  inline void normalize();

  // Operators
  inline ofHatQuaternion &operator=(const ofHatQuaternion &q);
  inline bool operator==(const ofHatQuaternion &q) const;
  inline bool operator!=(const ofHatQuaternion &q) const;
  inline const ofHatQuaternion
  operator*(double rhs) const; ///< Multiply by scalar
  inline const ofHatQuaternion
  operator*(const ofHatQuaternion &rhs) const; ///< Binary multiply
  inline ofHatVec3d
  operator*(const ofHatVec3d &v) const; ///< Rotate a vector by this quaternion.
  inline ofHatQuaternion &operator*=(double rhs); ///< Unary multiply by scalar
  inline ofHatQuaternion &
  operator*=(const ofHatQuaternion &rhs);             ///< Unary multiply
  inline ofHatQuaternion operator/(double rhs) const; ///< Divide by scalar
  inline const ofHatQuaternion
  operator/(const ofHatQuaternion &denom) const;  ///< Binary divide
  inline ofHatQuaternion &operator/=(double rhs); ///< Unary divide by scalar
  inline ofHatQuaternion &
  operator/=(const ofHatQuaternion &denom); ///< Unary divide
  inline const ofHatQuaternion
  operator+(const ofHatQuaternion &rhs) const; ///< Binary addition
  inline ofHatQuaternion &
  operator+=(const ofHatQuaternion &rhs); ///< Unary addition
  inline ofHatQuaternion &
  operator-=(const ofHatQuaternion &rhs); ///< Unary subtraction
  inline const ofHatQuaternion
  operator-(const ofHatQuaternion &rhs) const; ///< Binary subtraction
  inline const ofHatQuaternion
  operator-() const; ///< returns the negative of the
  friend ostream &operator<<(ostream &os, const ofHatQuaternion &q);
  friend istream &operator>>(istream &is, ofHatQuaternion &q);
};

// ----------------------------------------------------------------
// IMPLEMENTATION
// ----------------------------------------------------------------

//----------------------------------------
ofHatQuaternion::ofHatQuaternion() { _v.set(0, 0, 0, 1); }

//----------------------------------------
ofHatQuaternion::ofHatQuaternion(double x, double y, double z, double w) {
  _v.set(x, y, z, w);
}

//----------------------------------------
ofHatQuaternion::ofHatQuaternion(const ofHatVec4d &v) { _v = v; }

//----------------------------------------
ofHatQuaternion::ofHatQuaternion(double angle, const ofHatVec3d &axis) {
  makeRotate(angle, axis);
}

//----------------------------------------
ofHatQuaternion::ofHatQuaternion(double angle1, const ofHatVec3d &axis1,
                                 double angle2, const ofHatVec3d &axis2,
                                 double angle3, const ofHatVec3d &axis3) {
  makeRotate(angle1, axis1, angle2, axis2, angle3, axis3);
}

//----------------------------------------
ofHatQuaternion &ofHatQuaternion::operator=(const ofHatQuaternion &q) {
  _v = q._v;
  return *this;
}

//----------------------------------------
bool ofHatQuaternion::operator==(const ofHatQuaternion &q) const {
  return _v == q._v;
}

//----------------------------------------
bool ofHatQuaternion::operator!=(const ofHatQuaternion &q) const {
  return _v != q._v;
}

//----------------------------------------
// bool ofHatQuaternion::operator <(const ofHatQuaternion& q) const {
//    if(_v.x < v._v.x) return true;
//    else if(_v.x > v._v.x) return false;
//    else if(_v.y < v._v.y) return true;
//    else if(_v.y > v._v.y) return false;
//    else if(_v.z < v._v.z) return true;
//    else if(_v.z > v._v.z) return false;
//    else return (_v.w < v._v.w);
//}

//----------------------------------------
ofHatVec4d ofHatQuaternion::asVec4() const { return _v; }

//----------------------------------------
ofHatVec3d ofHatQuaternion::asVec3() const { return ofHatVec3d(_v); }

//----------------------------------------
void ofHatQuaternion::set(double x, double y, double z, double w) {
  _v.set(x, y, z, w);
}

//----------------------------------------
void ofHatQuaternion::set(const ofHatVec4d &v) { _v = v; }

//----------------------------------------
double &ofHatQuaternion::operator[](int i) { return _v[i]; }

//----------------------------------------
double ofHatQuaternion::operator[](int i) const { return _v[i]; }

//----------------------------------------
double &ofHatQuaternion::x() { return _v.x; }

//----------------------------------------
double &ofHatQuaternion::y() { return _v.y; }

//----------------------------------------
double &ofHatQuaternion::z() { return _v.z; }

//----------------------------------------
double &ofHatQuaternion::w() { return _v.w; }

//----------------------------------------
double ofHatQuaternion::x() const { return _v.x; }

//----------------------------------------
double ofHatQuaternion::y() const { return _v.y; }

//----------------------------------------
double ofHatQuaternion::z() const { return _v.z; }

//----------------------------------------
double ofHatQuaternion::w() const { return _v.w; }

//----------------------------------------
bool ofHatQuaternion::zeroRotation() const {
  return _v.x == 0.0 && _v.y == 0.0 && _v.z == 0.0 && _v.w == 1.0;
}

//----------------------------------------
const ofHatQuaternion ofHatQuaternion::operator*(double rhs) const {
  return ofHatQuaternion(_v.x * rhs, _v.y * rhs, _v.z * rhs, _v.w * rhs);
}

//----------------------------------------
ofHatQuaternion &ofHatQuaternion::operator*=(double rhs) {
  _v.x *= rhs;
  _v.y *= rhs;
  _v.z *= rhs;
  _v.w *= rhs;
  return *this; // enable nesting
}

//----------------------------------------
const ofHatQuaternion ofHatQuaternion::
operator*(const ofHatQuaternion &rhs) const {
  return ofHatQuaternion(
      rhs._v.w * _v.x + rhs._v.x * _v.w + rhs._v.y * _v.z - rhs._v.z * _v.y,
      rhs._v.w * _v.y - rhs._v.x * _v.z + rhs._v.y * _v.w + rhs._v.z * _v.x,
      rhs._v.w * _v.z + rhs._v.x * _v.y - rhs._v.y * _v.x + rhs._v.z * _v.w,
      rhs._v.w * _v.w - rhs._v.x * _v.x - rhs._v.y * _v.y - rhs._v.z * _v.z);
}

//----------------------------------------
ofHatQuaternion &ofHatQuaternion::operator*=(const ofHatQuaternion &rhs) {
  double x =
      rhs._v.w * _v.x + rhs._v.x * _v.w + rhs._v.y * _v.z - rhs._v.z * _v.y;
  double y =
      rhs._v.w * _v.y - rhs._v.x * _v.z + rhs._v.y * _v.w + rhs._v.z * _v.x;
  double z =
      rhs._v.w * _v.z + rhs._v.x * _v.y - rhs._v.y * _v.x + rhs._v.z * _v.w;
  _v.w = rhs._v.w * _v.w - rhs._v.x * _v.x - rhs._v.y * _v.y - rhs._v.z * _v.z;

  _v.z = z;
  _v.y = y;
  _v.x = x;

  return (*this); // enable nesting
}

//----------------------------------------
ofHatQuaternion ofHatQuaternion::operator/(double rhs) const {
  double div = 1.0f / rhs;
  return ofHatQuaternion(_v.x * div, _v.y * div, _v.z * div, _v.w * div);
}

//----------------------------------------
ofHatQuaternion &ofHatQuaternion::operator/=(double rhs) {
  double div = 1.0f / rhs;
  _v.x *= div;
  _v.y *= div;
  _v.z *= div;
  _v.w *= div;
  return *this;
}

//----------------------------------------
const ofHatQuaternion ofHatQuaternion::
operator/(const ofHatQuaternion &denom) const {
  return ((*this) * denom.inverse());
}

//----------------------------------------
ofHatQuaternion &ofHatQuaternion::operator/=(const ofHatQuaternion &denom) {
  (*this) = (*this) * denom.inverse();
  return (*this); // enable nesting
}

//----------------------------------------
const ofHatQuaternion ofHatQuaternion::
operator+(const ofHatQuaternion &rhs) const {
  return ofHatQuaternion(_v.x + rhs._v.x, _v.y + rhs._v.y, _v.z + rhs._v.z,
                         _v.w + rhs._v.w);
}

//----------------------------------------
ofHatQuaternion &ofHatQuaternion::operator+=(const ofHatQuaternion &rhs) {
  _v.x += rhs._v.x;
  _v.y += rhs._v.y;
  _v.z += rhs._v.z;
  _v.w += rhs._v.w;
  return *this; // enable nesting
}

//----------------------------------------
const ofHatQuaternion ofHatQuaternion::
operator-(const ofHatQuaternion &rhs) const {
  return ofHatQuaternion(_v.x - rhs._v.x, _v.y - rhs._v.y, _v.z - rhs._v.z,
                         _v.w - rhs._v.w);
}

//----------------------------------------
ofHatQuaternion &ofHatQuaternion::operator-=(const ofHatQuaternion &rhs) {
  _v.x -= rhs._v.x;
  _v.y -= rhs._v.y;
  _v.z -= rhs._v.z;
  _v.w -= rhs._v.w;
  return *this; // enable nesting
}

//----------------------------------------
const ofHatQuaternion ofHatQuaternion::operator-() const {
  return ofHatQuaternion(-_v.x, -_v.y, -_v.z, -_v.w);
}

//----------------------------------------
double ofHatQuaternion::length() const {
  return sqrt(_v.x * _v.x + _v.y * _v.y + _v.z * _v.z + _v.w * _v.w);
}

//----------------------------------------
double ofHatQuaternion::length2() const {
  return _v.x * _v.x + _v.y * _v.y + _v.z * _v.z + _v.w * _v.w;
}

//----------------------------------------
ofHatQuaternion ofHatQuaternion::conj() const {
  return ofHatQuaternion(-_v.x, -_v.y, -_v.z, _v.w);
}

//----------------------------------------
const ofHatQuaternion ofHatQuaternion::inverse() const {
  return conj() / length2();
}

//----------------------------------------
ofHatVec3d ofHatQuaternion::operator*(const ofHatVec3d &v) const {
  // nVidia SDK implementation
  ofHatVec3d uv, uuv;
  ofHatVec3d qvec(_v.x, _v.y, _v.z);
  uv = qvec.getCrossed(v);   // uv = qvec ^ v;
  uuv = qvec.getCrossed(uv); // uuv = qvec ^ uv;
  uv *= (2.0f * _v.w);
  uuv *= 2.0f;
  return v + uv + uuv;
}

void ofHatQuaternion::normalize() {
  double len = _v.w * _v.w + _v.x * _v.x + _v.y * _v.y + _v.z * _v.z;
  double factor = 1.0f / sqrt(len);
  _v.x *= factor;
  _v.y *= factor;
  _v.z *= factor;
  _v.w *= factor;
}

#endif