//!
//! @file ofHatMatrix3x3.h
//! @brief ofHatMatrix3x3 header file
//! @author HATTORI Kohei
//! @date 4/21/2016
//!

#ifndef __ofHatMath__ofHatMatrix3x3__
#define __ofHatMath__ofHatMatrix3x3__

#include "ofConstants.h"

class ofHatMatrix3x3 {

public:
  double a;
  double b;
  double c;
  double d;
  double e;
  double f;
  double g;
  double h;
  double i;

public:
  // Constructor
  ofHatMatrix3x3(double _a = 0.0, double _b = 0.0, double _c = 0.0,
                 double _d = 0.0, double _e = 0.0, double _f = 0.0,
                 double _g = 0.0, double _h = 0.0, double _i = 0.0);

  // Matrix access
  void set(double _a, double _b, double _c, double _d, double _e, double _f,
           double _g, double _h, double _i);
  double &operator[](const int &index);

  // Functions
  void transpose();
  ofHatMatrix3x3 transpose(const ofHatMatrix3x3 &A);
  double determinant() const;
  double determinant(const ofHatMatrix3x3 &A);
  ofHatMatrix3x3 inverse(const ofHatMatrix3x3 &A);
  void invert();
  ofHatMatrix3x3 entrywiseTimes(const ofHatMatrix3x3 &A);

  // name Operators
  ofHatMatrix3x3 operator+(const ofHatMatrix3x3 &B);
  void operator+=(const ofHatMatrix3x3 &B);
  ofHatMatrix3x3 operator-(const ofHatMatrix3x3 &B);
  void operator-=(const ofHatMatrix3x3 &B);
  ofHatMatrix3x3 operator*(double scalar);
  void operator*=(const ofHatMatrix3x3 &B);
  void operator*=(double scalar);
  ofHatMatrix3x3 operator*(const ofHatMatrix3x3 &B);
  ofHatMatrix3x3 operator/(double scalar);
  void operator/=(const ofHatMatrix3x3 &B);
  void operator/=(double scalar);
  friend ostream &operator<<(ostream &os, const ofHatMatrix3x3 &M);
  friend istream &operator>>(istream &is, ofHatMatrix3x3 &M);
};

#endif