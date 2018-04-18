//!
//! @file ofHatMatrix4x4.h
//! @brief ofHatMatrix4x4 header file
//! @author HATTORI Kohei
//! @date 4/21/2016
//!

#ifndef __ofHatMath__ofHatMatrix4x4__
#define __ofHatMath__ofHatMatrix4x4__

#include "ofConstants.h"
#include "ofHatQuaternion.h"
#include "ofHatVec3d.h"
#include "ofHatVec4d.h"
#include <cmath>

class ofHatMatrix4x4 {
public:
  ofHatVec4d _mat[4];

public:
  // name Constructors
  ofHatMatrix4x4() { makeIdentityMatrix(); }
  ofHatMatrix4x4(const ofHatMatrix4x4 &mat) { set(mat.getPtr()); }
  ofHatMatrix4x4(double const *const ptr) { set(ptr); }
  ofHatMatrix4x4(const ofHatQuaternion &quat) { makeRotationMatrix(quat); }
  ofHatMatrix4x4(double a00, double a01, double a02, double a03, double a10,
                 double a11, double a12, double a13, double a20, double a21,
                 double a22, double a23, double a30, double a31, double a32,
                 double a33);
  ~ofHatMatrix4x4() {}

  // make* Methods
  void makeIdentityMatrix();

  // Scale
  void makeScaleMatrix(const ofHatVec3d &);
  void makeScaleMatrix(double, double, double);

  // Translation
  void makeTranslationMatrix(const ofHatVec3d &);
  void makeTranslationMatrix(double, double, double);

  // Rotation
  void makeRotationMatrix(const ofHatVec3d &from, const ofHatVec3d &to);
  void makeRotationMatrix(double angle, const ofHatVec3d &axis);
  void makeRotationMatrix(double angle, double x, double y, double z);
  void makeRotationMatrix(const ofHatQuaternion &quaternion);
  void makeRotationMatrix(double angle1, const ofHatVec3d &axis1, double angle2,
                          const ofHatVec3d &axis2, double angle3,
                          const ofHatVec3d &axis3);

  // Make* methods related to another matrix
  bool makeInvertOf(const ofHatMatrix4x4 &rhs);
  void makeOrthoNormalOf(const ofHatMatrix4x4 &rhs);
  void makeFromMultiplicationOf(const ofHatMatrix4x4 &, const ofHatMatrix4x4 &);

  // View matrix make*
  void makeOrthoMatrix(double left, double right, double bottom, double top,
                       double zNear, double zFar);
  void makeOrtho2DMatrix(double left, double right, double bottom, double top);
  void makeFrustumMatrix(double left, double right, double bottom, double top,
                         double zNear, double zFar);
  void makePerspectiveMatrix(double fovy, double aspectRatio, double zNear,
                             double zFar);
  void makeLookAtMatrix(const ofHatVec3d &eye, const ofHatVec3d &center,
                        const ofHatVec3d &up);
  void makeLookAtViewMatrix(const ofHatVec3d &eye, const ofHatVec3d &center,
                            const ofHatVec3d &up);

  // Static new* matrix functions
  inline static ofHatMatrix4x4 newIdentityMatrix(void);
  inline static ofHatMatrix4x4 newScaleMatrix(const ofHatVec3d &sv);
  inline static ofHatMatrix4x4 newScaleMatrix(double sx, double sy, double sz);
  inline static ofHatMatrix4x4 newTranslationMatrix(const ofHatVec3d &dv);
  inline static ofHatMatrix4x4 newTranslationMatrix(double x, double y,
                                                    double z);
  inline static ofHatMatrix4x4 newRotationMatrix(const ofHatVec3d &from,
                                                 const ofHatVec3d &to);
  inline static ofHatMatrix4x4 newRotationMatrix(double angle, double x,
                                                 double y, double z);
  inline static ofHatMatrix4x4 newRotationMatrix(double angle,
                                                 const ofHatVec3d &axis);
  inline static ofHatMatrix4x4
  newRotationMatrix(double angle1, const ofHatVec3d &axis1, double angle2,
                    const ofHatVec3d &axis2, double angle3,
                    const ofHatVec3d &axis3);
  inline static ofHatMatrix4x4 newRotationMatrix(const ofHatQuaternion &quat);
  inline static ofHatMatrix4x4 newOrthoMatrix(double left, double right,
                                              double bottom, double top,
                                              double zNear, double zFar);
  inline static ofHatMatrix4x4 newOrtho2DMatrix(double left, double right,
                                                double bottom, double top);
  inline static ofHatMatrix4x4 newFrustumMatrix(double left, double right,
                                                double bottom, double top,
                                                double zNear, double zFar);
  inline static ofHatMatrix4x4 newPerspectiveMatrix(double fovy,
                                                    double aspectRatio,
                                                    double zNear, double zFar);
  inline static ofHatMatrix4x4 newLookAtMatrix(const ofHatVec3d &eye,
                                               const ofHatVec3d &center,
                                               const ofHatVec3d &up);

  // Accessors
  double &operator()(std::size_t row, std::size_t col) {
    return _mat[row][col];
  }
  double operator()(std::size_t row, std::size_t col) const {
    return _mat[row][col];
  }
  ofHatVec3d getRowAsVec3f(std::size_t i) const {
    return ofHatVec3d(_mat[i][0], _mat[i][1], _mat[i][2]);
  }
  ofHatVec4d getRowAsVec4f(std::size_t i) const { return _mat[i]; }
  friend ostream &operator<<(ostream &os, const ofHatMatrix4x4 &M);
  friend istream &operator>>(istream &is, ofHatMatrix4x4 &M);
  double *getPtr() { return (double *)_mat; }
  const double *getPtr() const { return (const double *)_mat; }

  // Checking
  bool isValid() const { return !isNaN(); }
  bool isNaN() const;
  bool isIdentity() const;

  // Setters
  ofHatMatrix4x4 &operator=(const ofHatMatrix4x4 &rhs);
  void set(const ofHatMatrix4x4 &rhs);
  void set(double const *const ptr);
  void set(double a00, double a01, double a02, double a03, double a10,
           double a11, double a12, double a13, double a20, double a21,
           double a22, double a23, double a30, double a31, double a32,
           double a33);

  // Getters
  ofHatMatrix4x4 getInverse() const;
  bool getOrtho(double &left, double &right, double &bottom, double &top,
                double &zNear, double &zFar) const;
  bool getFrustum(double &left, double &right, double &bottom, double &top,
                  double &zNear, double &zFar) const;
  bool getPerspective(double &fovy, double &aspectRatio, double &zNear,
                      double &zFar) const;
  void getLookAt(ofHatVec3d &eye, ofHatVec3d &center, ofHatVec3d &up,
                 double lookDistance = 1.0f) const;
  void decompose(ofHatVec3d &translation, ofHatQuaternion &rotation,
                 ofHatVec3d &scale, ofHatQuaternion &so) const;
  inline static ofHatMatrix4x4 getInverseOf(const ofHatMatrix4x4 &matrix);
  inline static ofHatMatrix4x4 getTransposedOf(const ofHatMatrix4x4 &matrix);
  inline static ofHatMatrix4x4 getOrthoNormalOf(const ofHatMatrix4x4 &matrix);

  // Matrix multiplication
  inline ofHatVec3d postMult(const ofHatVec3d &v) const;
  inline ofHatVec4d postMult(const ofHatVec4d &v) const;
  void postMult(const ofHatMatrix4x4 &);
  inline ofHatVec3d preMult(const ofHatVec3d &v) const;
  inline ofHatVec4d preMult(const ofHatVec4d &v) const;
  void preMult(const ofHatMatrix4x4 &);
  inline void operator*=(const ofHatMatrix4x4 &other) {
    if (this == &other) {
      ofHatMatrix4x4 temp(other);
      postMult(temp);
    } else
      postMult(other);
  }
  inline ofHatMatrix4x4 operator*(const ofHatMatrix4x4 &m) const {
    ofHatMatrix4x4 r;
    r.makeFromMultiplicationOf(*this, m);
    return r;
  }
  inline ofHatVec3d operator*(const ofHatVec3d &v) const { return postMult(v); }
  inline ofHatVec4d operator*(const ofHatVec4d &v) const { return postMult(v); }
  inline void postMultTranslate(const ofHatVec3d &v);
  inline void postMultScale(const ofHatVec3d &v);
  inline void postMultRotate(const ofHatQuaternion &q);
  inline void postMultTranslate(double x, double y, double z);
  inline void postMultRotate(double angle, double x, double y, double z);
  inline void postMultScale(double x, double y, double z);
  inline void preMultScale(const ofHatVec3d &v);
  inline void preMultTranslate(const ofHatVec3d &v);
  inline void preMultRotate(const ofHatQuaternion &q);

  // Matrix transformation
  // Set methods
  void setRotate(const ofHatQuaternion &q);
  void setTranslation(double tx, double ty, double tz);
  void setTranslation(const ofHatVec3d &v);

  // PostMult Transformations
  void rotate(double angle, double x, double y, double z);
  void rotateRad(double angle, double x, double y, double z);
  void rotate(const ofHatQuaternion &q);
  void translate(double tx, double ty, double tz);
  void translate(const ofHatVec3d &v);
  void scale(double x, double y, double z);
  void scale(const ofHatVec3d &v);

  // PreMult Transformations
  void glRotate(double angle, double x, double y, double z);
  void glRotateRad(double angle, double x, double y, double z);
  void glRotate(const ofHatQuaternion &q);
  void glTranslate(double tx, double ty, double tz);
  void glTranslate(const ofHatVec3d &v);
  void glScale(double x, double y, double z);
  void glScale(const ofHatVec3d &v);

  // Get Methods
  ofHatQuaternion getRotate() const;
  ofHatVec3d getTranslation() const;
  ofHatVec3d getScale() const;
  inline static ofHatVec3d transform3x3(const ofHatVec3d &v,
                                        const ofHatMatrix4x4 &m);
  inline static ofHatVec3d transform3x3(const ofHatMatrix4x4 &m,
                                        const ofHatVec3d &v);
};

/// \cond INTERNAL

//--------------------------------------------------
// implementation of inline methods

inline bool ofHatMatrix4x4::isNaN() const {

#if (_MSC_VER) || defined(TARGET_ANDROID)
#ifndef isnan
#define isnan(a) ((a) != (a))
#endif

  return isnan(_mat[0][0]) || isnan(_mat[0][1]) || isnan(_mat[0][2]) ||
         isnan(_mat[0][3]) || isnan(_mat[1][0]) || isnan(_mat[1][1]) ||
         isnan(_mat[1][2]) || isnan(_mat[1][3]) || isnan(_mat[2][0]) ||
         isnan(_mat[2][1]) || isnan(_mat[2][2]) || isnan(_mat[2][3]) ||
         isnan(_mat[3][0]) || isnan(_mat[3][1]) || isnan(_mat[3][2]) ||
         isnan(_mat[3][3]);

#else
  return std::isnan(_mat[0][0]) || std::isnan(_mat[0][1]) ||
         std::isnan(_mat[0][2]) || std::isnan(_mat[0][3]) ||
         std::isnan(_mat[1][0]) || std::isnan(_mat[1][1]) ||
         std::isnan(_mat[1][2]) || std::isnan(_mat[1][3]) ||
         std::isnan(_mat[2][0]) || std::isnan(_mat[2][1]) ||
         std::isnan(_mat[2][2]) || std::isnan(_mat[2][3]) ||
         std::isnan(_mat[3][0]) || std::isnan(_mat[3][1]) ||
         std::isnan(_mat[3][2]) || std::isnan(_mat[3][3]);

#endif
}

inline ostream &operator<<(ostream &os, const ofHatMatrix4x4 &M) {
  int w = 8;
  os << setw(w) << M._mat[0][0] << ", " << setw(w) << M._mat[0][1] << ", "
     << setw(w) << M._mat[0][2] << ", " << setw(w) << M._mat[0][3] << std::endl;

  os << setw(w) << M._mat[1][0] << ", " << setw(w) << M._mat[1][1] << ", "
     << setw(w) << M._mat[1][2] << ", " << setw(w) << M._mat[1][3] << std::endl;

  os << setw(w) << M._mat[2][0] << ", " << setw(w) << M._mat[2][1] << ", "
     << setw(w) << M._mat[2][2] << ", " << setw(w) << M._mat[2][3] << std::endl;

  os << setw(w) << M._mat[3][0] << ", " << setw(w) << M._mat[3][1] << ", "
     << setw(w) << M._mat[3][2] << ", " << setw(w) << M._mat[3][3];

  return os;
}

inline istream &operator>>(istream &is, ofHatMatrix4x4 &M) {
  is >> M._mat[0][0];
  is.ignore(2);
  is >> M._mat[0][1];
  is.ignore(2);
  is >> M._mat[0][2];
  is.ignore(2);
  is >> M._mat[0][3];
  is.ignore(1);

  is >> M._mat[1][0];
  is.ignore(2);
  is >> M._mat[1][1];
  is.ignore(2);
  is >> M._mat[1][2];
  is.ignore(2);
  is >> M._mat[1][3];
  is.ignore(1);

  is >> M._mat[2][0];
  is.ignore(2);
  is >> M._mat[2][1];
  is.ignore(2);
  is >> M._mat[2][2];
  is.ignore(2);
  is >> M._mat[2][3];
  is.ignore(1);

  is >> M._mat[3][0];
  is.ignore(2);
  is >> M._mat[3][1];
  is.ignore(2);
  is >> M._mat[3][2];
  is.ignore(2);
  is >> M._mat[3][3];
  return is;
}

inline ofHatMatrix4x4 &ofHatMatrix4x4::operator=(const ofHatMatrix4x4 &rhs) {
  if (&rhs == this)
    return *this;
  set(rhs.getPtr());
  return *this;
}

inline void ofHatMatrix4x4::set(const ofHatMatrix4x4 &rhs) {
  set(rhs.getPtr());
}

inline void ofHatMatrix4x4::set(double const *const ptr) {
  double *local_ptr = (double *)_mat;
  for (std::size_t i = 0; i < 16; ++i)
    local_ptr[i] = (double)ptr[i];
}

inline bool ofHatMatrix4x4::isIdentity() const {
  return _mat[0][0] == 1.0f && _mat[0][1] == 0.0f && _mat[0][2] == 0.0f &&
         _mat[0][3] == 0.0f && _mat[1][0] == 0.0f && _mat[1][1] == 1.0f &&
         _mat[1][2] == 0.0f && _mat[1][3] == 0.0f && _mat[2][0] == 0.0f &&
         _mat[2][1] == 0.0f && _mat[2][2] == 1.0f && _mat[2][3] == 0.0f &&
         _mat[3][0] == 0.0f && _mat[3][1] == 0.0f && _mat[3][2] == 0.0f &&
         _mat[3][3] == 1.0f;
}

inline void ofHatMatrix4x4::makeOrtho2DMatrix(double left, double right,
                                              double bottom, double top) {
  makeOrthoMatrix(left, right, bottom, top, -1.0, 1.0);
}

inline ofHatVec3d ofHatMatrix4x4::getTranslation() const {
  return ofHatVec3d(_mat[3][0], _mat[3][1], _mat[3][2]);
}

inline ofHatVec3d ofHatMatrix4x4::getScale() const {
  ofHatVec3d x_vec(_mat[0][0], _mat[1][0], _mat[2][0]);
  ofHatVec3d y_vec(_mat[0][1], _mat[1][1], _mat[2][1]);
  ofHatVec3d z_vec(_mat[0][2], _mat[1][2], _mat[2][2]);
  return ofHatVec3d(x_vec.length(), y_vec.length(), z_vec.length());
}

// static utility methods
inline ofHatMatrix4x4 ofHatMatrix4x4::newIdentityMatrix(void) {
  ofHatMatrix4x4 m;
  m.makeIdentityMatrix();
  return m;
}

inline ofHatMatrix4x4 ofHatMatrix4x4::newScaleMatrix(double sx, double sy,
                                                     double sz) {
  ofHatMatrix4x4 m;
  m.makeScaleMatrix(sx, sy, sz);
  return m;
}

inline ofHatMatrix4x4 ofHatMatrix4x4::newScaleMatrix(const ofHatVec3d &v) {
  return newScaleMatrix(v.x, v.y, v.z);
}

inline ofHatMatrix4x4 ofHatMatrix4x4::newTranslationMatrix(double tx, double ty,
                                                           double tz) {
  ofHatMatrix4x4 m;
  m.makeTranslationMatrix(tx, ty, tz);
  return m;
}

inline ofHatMatrix4x4
ofHatMatrix4x4::newTranslationMatrix(const ofHatVec3d &v) {
  return newTranslationMatrix(v.x, v.y, v.z);
}

inline ofHatMatrix4x4
ofHatMatrix4x4::newRotationMatrix(const ofHatQuaternion &q) {
  return ofHatMatrix4x4(q);
}
inline ofHatMatrix4x4 ofHatMatrix4x4::newRotationMatrix(double angle, double x,
                                                        double y, double z) {
  ofHatMatrix4x4 m;
  m.makeRotationMatrix(angle, x, y, z);
  return m;
}
inline ofHatMatrix4x4
ofHatMatrix4x4::newRotationMatrix(double angle, const ofHatVec3d &axis) {
  ofHatMatrix4x4 m;
  m.makeRotationMatrix(angle, axis);
  return m;
}
inline ofHatMatrix4x4
ofHatMatrix4x4::newRotationMatrix(double angle1, const ofHatVec3d &axis1,
                                  double angle2, const ofHatVec3d &axis2,
                                  double angle3, const ofHatVec3d &axis3) {
  ofHatMatrix4x4 m;
  m.makeRotationMatrix(angle1, axis1, angle2, axis2, angle3, axis3);
  return m;
}
inline ofHatMatrix4x4 ofHatMatrix4x4::newRotationMatrix(const ofHatVec3d &from,
                                                        const ofHatVec3d &to) {
  ofHatMatrix4x4 m;
  m.makeRotationMatrix(from, to);
  return m;
}

inline ofHatMatrix4x4
ofHatMatrix4x4::getInverseOf(const ofHatMatrix4x4 &matrix) {
  ofHatMatrix4x4 m;
  m.makeInvertOf(matrix);
  return m;
}

inline ofHatMatrix4x4
ofHatMatrix4x4::getTransposedOf(const ofHatMatrix4x4 &matrix) {
  ofHatMatrix4x4 m(matrix._mat[0][0], matrix._mat[1][0], matrix._mat[2][0],
                   matrix._mat[3][0], matrix._mat[0][1], matrix._mat[1][1],
                   matrix._mat[2][1], matrix._mat[3][1], matrix._mat[0][2],
                   matrix._mat[1][2], matrix._mat[2][2], matrix._mat[3][2],
                   matrix._mat[0][3], matrix._mat[1][3], matrix._mat[2][3],
                   matrix._mat[3][3]);
  return m;
}

inline ofHatMatrix4x4
ofHatMatrix4x4::getOrthoNormalOf(const ofHatMatrix4x4 &matrix) {
  ofHatMatrix4x4 m;
  m.makeOrthoNormalOf(matrix);
  return m;
}

inline ofHatMatrix4x4 ofHatMatrix4x4::newOrthoMatrix(double left, double right,
                                                     double bottom, double top,
                                                     double zNear,
                                                     double zFar) {
  ofHatMatrix4x4 m;
  m.makeOrthoMatrix(left, right, bottom, top, zNear, zFar);
  return m;
}

inline ofHatMatrix4x4 ofHatMatrix4x4::newOrtho2DMatrix(double left,
                                                       double right,
                                                       double bottom,
                                                       double top) {
  ofHatMatrix4x4 m;
  m.makeOrtho2DMatrix(left, right, bottom, top);
  return m;
}

inline ofHatMatrix4x4
ofHatMatrix4x4::newFrustumMatrix(double left, double right, double bottom,
                                 double top, double zNear, double zFar) {
  ofHatMatrix4x4 m;
  m.makeFrustumMatrix(left, right, bottom, top, zNear, zFar);
  return m;
}

inline ofHatMatrix4x4 ofHatMatrix4x4::newPerspectiveMatrix(double fovy,
                                                           double aspectRatio,
                                                           double zNear,
                                                           double zFar) {
  ofHatMatrix4x4 m;
  m.makePerspectiveMatrix(fovy, aspectRatio, zNear, zFar);
  return m;
}

inline ofHatMatrix4x4 ofHatMatrix4x4::newLookAtMatrix(const ofHatVec3d &eye,
                                                      const ofHatVec3d &center,
                                                      const ofHatVec3d &up) {
  ofHatMatrix4x4 m;
  m.makeLookAtMatrix(eye, center, up);
  return m;
}

inline ofHatVec3d ofHatMatrix4x4::postMult(const ofHatVec3d &v) const {
  double d = 1.0f / (_mat[3][0] * v.x + _mat[3][1] * v.y + _mat[3][2] * v.z +
                     _mat[3][3]);
  return ofHatVec3d(
      (_mat[0][0] * v.x + _mat[0][1] * v.y + _mat[0][2] * v.z + _mat[0][3]) * d,
      (_mat[1][0] * v.x + _mat[1][1] * v.y + _mat[1][2] * v.z + _mat[1][3]) * d,
      (_mat[2][0] * v.x + _mat[2][1] * v.y + _mat[2][2] * v.z + _mat[2][3]) *
          d);
}

inline ofHatVec3d ofHatMatrix4x4::preMult(const ofHatVec3d &v) const {
  double d = 1.0f / (_mat[0][3] * v.x + _mat[1][3] * v.y + _mat[2][3] * v.z +
                     _mat[3][3]);
  return ofHatVec3d(
      (_mat[0][0] * v.x + _mat[1][0] * v.y + _mat[2][0] * v.z + _mat[3][0]) * d,
      (_mat[0][1] * v.x + _mat[1][1] * v.y + _mat[2][1] * v.z + _mat[3][1]) * d,
      (_mat[0][2] * v.x + _mat[1][2] * v.y + _mat[2][2] * v.z + _mat[3][2]) *
          d);
}

/// \brief post-multiplies the vector by the matrix (i.e. returns M mult v).
/// The vector is implicitly treated as a column-matrix
inline ofHatVec4d ofHatMatrix4x4::postMult(const ofHatVec4d &v) const {
  return ofHatVec4d((_mat[0][0] * v.x + _mat[0][1] * v.y + _mat[0][2] * v.z +
                     _mat[0][3] * v.w),
                    (_mat[1][0] * v.x + _mat[1][1] * v.y + _mat[1][2] * v.z +
                     _mat[1][3] * v.w),
                    (_mat[2][0] * v.x + _mat[2][1] * v.y + _mat[2][2] * v.z +
                     _mat[2][3] * v.w),
                    (_mat[3][0] * v.x + _mat[3][1] * v.y + _mat[3][2] * v.z +
                     _mat[3][3] * v.w));
}

/// \brief pre-multiplies the vector by the matrix (i.e. returns v mult M)
/// The vector is implicitly treated as a row-matrix
inline ofHatVec4d ofHatMatrix4x4::preMult(const ofHatVec4d &v) const {
  return ofHatVec4d((_mat[0][0] * v.x + _mat[1][0] * v.y + _mat[2][0] * v.z +
                     _mat[3][0] * v.w),
                    (_mat[0][1] * v.x + _mat[1][1] * v.y + _mat[2][1] * v.z +
                     _mat[3][1] * v.w),
                    (_mat[0][2] * v.x + _mat[1][2] * v.y + _mat[2][2] * v.z +
                     _mat[3][2] * v.w),
                    (_mat[0][3] * v.x + _mat[1][3] * v.y + _mat[2][3] * v.z +
                     _mat[3][3] * v.w));
}

/// \brief performs a pre-multiplication transformation on the vector using only
/// the
/// upper left 3x3 portion of the matrix (i.e. only the rotation part).
inline ofHatVec3d ofHatMatrix4x4::transform3x3(const ofHatVec3d &v,
                                               const ofHatMatrix4x4 &m) {
  return ofHatVec3d(
      (m._mat[0][0] * v.x + m._mat[1][0] * v.y + m._mat[2][0] * v.z),
      (m._mat[0][1] * v.x + m._mat[1][1] * v.y + m._mat[2][1] * v.z),
      (m._mat[0][2] * v.x + m._mat[1][2] * v.y + m._mat[2][2] * v.z));
}

/// \brief performs a post-multiplication transformation on the vector using
/// only the
/// upper left 3x3 portion of the matrix (i.e. only the rotation part).
inline ofHatVec3d ofHatMatrix4x4::transform3x3(const ofHatMatrix4x4 &m,
                                               const ofHatVec3d &v) {
  return ofHatVec3d(
      (m._mat[0][0] * v.x + m._mat[0][1] * v.y + m._mat[0][2] * v.z),
      (m._mat[1][0] * v.x + m._mat[1][1] * v.y + m._mat[1][2] * v.z),
      (m._mat[2][0] * v.x + m._mat[2][1] * v.y + m._mat[2][2] * v.z));
}

/// \brief translates this matrix by treating the ofHatVec3d like a translation
/// matrix,
/// and multiplying this Matrix by it in a pre-multiplication manner (T mult M)
inline void ofHatMatrix4x4::preMultTranslate(const ofHatVec3d &v) {
  for (unsigned i = 0; i < 3; ++i) {
    double tmp = v.getPtr()[i];
    if (tmp == 0)
      continue;
    _mat[3][0] += tmp * _mat[i][0];
    _mat[3][1] += tmp * _mat[i][1];
    _mat[3][2] += tmp * _mat[i][2];
    _mat[3][3] += tmp * _mat[i][3];
  }
}

/// \brief translates this matrix by treating the ofHatVec3d like a translation
/// matrix,
/// and multiplying this Matrix by it in a post-multiplication manner (M mult T)
inline void ofHatMatrix4x4::postMultTranslate(const ofHatVec3d &v) {
  for (std::size_t i = 0; i < 3; ++i) {
    double tmp = v.getPtr()[i];
    if (tmp == 0)
      continue;
    _mat[0][i] += tmp * _mat[0][3];
    _mat[1][i] += tmp * _mat[1][3];
    _mat[2][i] += tmp * _mat[2][3];
    _mat[3][i] += tmp * _mat[3][3];
  }
}

// AARON METHOD
/// \brief the positional argument version of the above
inline void ofHatMatrix4x4::postMultTranslate(double x, double y, double z) {
  if (x != 0) {
    _mat[0][0] += x * _mat[0][3];
    _mat[1][0] += x * _mat[1][3];
    _mat[2][0] += x * _mat[2][3];
    _mat[3][0] += x * _mat[3][3];
  }
  if (y != 0) {
    _mat[0][1] += y * _mat[0][3];
    _mat[1][1] += y * _mat[1][3];
    _mat[2][1] += y * _mat[2][3];
    _mat[3][1] += y * _mat[3][3];
  }
  if (z != 0) {
    _mat[0][2] += z * _mat[0][3];
    _mat[1][2] += z * _mat[1][3];
    _mat[2][2] += z * _mat[2][3];
    _mat[3][2] += z * _mat[3][3];
  }
}

/// \brief treats the ofHatVec3d like a scaling matrix and edits this Matrix
/// by multiplying the vector with it in a pre-multiplication style (V mult M)
inline void ofHatMatrix4x4::preMultScale(const ofHatVec3d &v) {
  _mat[0][0] *= v.getPtr()[0];
  _mat[0][1] *= v.getPtr()[0];
  _mat[0][2] *= v.getPtr()[0];
  _mat[0][3] *= v.getPtr()[0];
  _mat[1][0] *= v.getPtr()[1];
  _mat[1][1] *= v.getPtr()[1];
  _mat[1][2] *= v.getPtr()[1];
  _mat[1][3] *= v.getPtr()[1];
  _mat[2][0] *= v.getPtr()[2];
  _mat[2][1] *= v.getPtr()[2];
  _mat[2][2] *= v.getPtr()[2];
  _mat[2][3] *= v.getPtr()[2];
}

/// \brief treats the ofHatVec3d like a scaling matrix and edits this Matrix
/// by multiplying the vector with it in a post-multiplication style (M mult V)
inline void ofHatMatrix4x4::postMultScale(const ofHatVec3d &v) {
  _mat[0][0] *= v.getPtr()[0];
  _mat[1][0] *= v.getPtr()[0];
  _mat[2][0] *= v.getPtr()[0];
  _mat[3][0] *= v.getPtr()[0];
  _mat[0][1] *= v.getPtr()[1];
  _mat[1][1] *= v.getPtr()[1];
  _mat[2][1] *= v.getPtr()[1];
  _mat[3][1] *= v.getPtr()[1];
  _mat[0][2] *= v.getPtr()[2];
  _mat[1][2] *= v.getPtr()[2];
  _mat[2][2] *= v.getPtr()[2];
  _mat[3][2] *= v.getPtr()[2];
}

/// \brief rotates this Matrix by the provided quaternion
inline void ofHatMatrix4x4::rotate(const ofHatQuaternion &q) {
  postMultRotate(q);
}

/// \brief rotates this Matrix by the provided angle (in degrees) around an axis
/// defined by the three values
inline void ofHatMatrix4x4::rotate(double angle, double x, double y, double z) {
  postMultRotate(angle, x, y, z);
}

/// \brief Rotates this Matrix by the provided angle (in Radians) around an axis
/// defined by the three values
inline void ofHatMatrix4x4::rotateRad(double angle, double x, double y,
                                      double z) {
  postMultRotate(angle * static_cast<double>(RAD_TO_DEG), x, y, z);
}

/// \brief Translates this matrix by the provided amount
inline void ofHatMatrix4x4::translate(double tx, double ty, double tz) {
  postMultTranslate(tx, ty, tz);
}

/// \brief Translates this matrix by the provided vector
inline void ofHatMatrix4x4::translate(const ofHatVec3d &v) {
  postMultTranslate(v);
}

/// \brief scales this matrix by the provided scales
inline void ofHatMatrix4x4::scale(double x, double y, double z) {
  postMultScale(x, y, z);
}

/// \brief scales this matrix, treating the ofHatVec3d as the diagonal of a
/// scaling matrix.
inline void ofHatMatrix4x4::scale(const ofHatVec3d &v) { postMultScale(v); }

/// implementation of the gl-style pre-multiplication versions of the above
/// functions
inline void ofHatMatrix4x4::glRotate(double angle, double x, double y,
                                     double z) {
  preMultRotate(ofHatQuaternion(angle, ofHatVec3d(x, y, z)));
}

inline void ofHatMatrix4x4::glRotateRad(double angle, double x, double y,
                                        double z) {
  preMultRotate(ofHatQuaternion(angle * static_cast<double>(RAD_TO_DEG),
                                ofHatVec3d(x, y, z)));
}

inline void ofHatMatrix4x4::glRotate(const ofHatQuaternion &q) {
  preMultRotate(q);
}

inline void ofHatMatrix4x4::glTranslate(double tx, double ty, double tz) {
  preMultTranslate(ofHatVec3d(tx, ty, tz));
}

inline void ofHatMatrix4x4::glTranslate(const ofHatVec3d &v) {
  preMultTranslate(v);
}

inline void ofHatMatrix4x4::glScale(double x, double y, double z) {
  preMultScale(ofHatVec3d(x, y, z));
}

inline void ofHatMatrix4x4::glScale(const ofHatVec3d &v) { preMultScale(v); }

// AARON METHOD
inline void ofHatMatrix4x4::postMultScale(double x, double y, double z) {
  _mat[0][0] *= x;
  _mat[1][0] *= x;
  _mat[2][0] *= x;
  _mat[3][0] *= x;
  _mat[0][1] *= y;
  _mat[1][1] *= y;
  _mat[2][1] *= y;
  _mat[3][1] *= y;
  _mat[0][2] *= z;
  _mat[1][2] *= z;
  _mat[2][2] *= z;
  _mat[3][2] *= z;
}

inline void ofHatMatrix4x4::preMultRotate(const ofHatQuaternion &q) {
  if (q.zeroRotation())
    return;
  ofHatMatrix4x4 r;
  r.setRotate(q);
  preMult(r);
}

inline void ofHatMatrix4x4::postMultRotate(const ofHatQuaternion &q) {
  if (q.zeroRotation())
    return;
  ofHatMatrix4x4 r;
  r.setRotate(q);
  postMult(r);
}

// AARON METHOD
inline void ofHatMatrix4x4::postMultRotate(double angle, double x, double y,
                                           double z) {
  ofHatMatrix4x4 r;
  r.makeRotationMatrix(angle, x, y, z);
  postMult(r);
}

/// \brief provides Vector3 * Matrix multiplication. Vectors are implicitly
/// treated as row-matrices.
inline ofHatVec3d operator*(const ofHatVec3d &v, const ofHatMatrix4x4 &m) {
  return m.preMult(v);
}
/// \brief provides Vector4 * Matrix multiplication. Vectors are implicitly
/// treated as row-matrices.
inline ofHatVec4d operator*(const ofHatVec4d &v, const ofHatMatrix4x4 &m) {
  return m.preMult(v);
}

#endif