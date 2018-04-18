//!
//! @file ofHatQuaternion.cpp
//! @brief ofHatQuaternion source file
//! @author HATTORI Kohei
//! @date 4/21/2016
//!

#include "ofHatMath.h"
#include "ofHatMatrix4x4.h"
#include "ofHatQuaternion.h"

void ofHatQuaternion::set(const ofHatMatrix4x4 &matrix) {
  *this = matrix.getRotate();
}

void ofHatQuaternion::get(ofHatMatrix4x4 &matrix) const {
  matrix.makeRotationMatrix(*this);
}

/// Set the elements of the Quat to represent a rotation of angle
/// (degrees) around the axis (x,y,z)
void ofHatQuaternion::makeRotate(double angle, double x, double y, double z) {
  angle = ofHatDegToRad(angle);

  const double epsilon = 0.0000001f;

  double length = sqrtf(x * x + y * y + z * z);
  if (length < epsilon) {
    // ~zero length axis, so reset rotation to zero.
    *this = ofHatQuaternion();
    return;
  }

  double inversenorm = 1.0f / length;
  double coshalfangle = cosf(0.5f * angle);
  double sinhalfangle = sinf(0.5f * angle);

  _v.x = x * sinhalfangle * inversenorm;
  _v.y = y * sinhalfangle * inversenorm;
  _v.z = z * sinhalfangle * inversenorm;
  _v.w = coshalfangle;
}

void ofHatQuaternion::makeRotate(double angle, const ofHatVec3d &vec) {
  makeRotate(angle, vec.x, vec.y, vec.z);
}

void ofHatQuaternion::makeRotate(double angle1, const ofHatVec3d &axis1,
                                 double angle2, const ofHatVec3d &axis2,
                                 double angle3, const ofHatVec3d &axis3) {
  ofHatQuaternion q1;
  q1.makeRotate(angle1, axis1);
  ofHatQuaternion q2;
  q2.makeRotate(angle2, axis2);
  ofHatQuaternion q3;
  q3.makeRotate(angle3, axis3);

  *this = q1 * q2 * q3;
}

/** Make a rotation Quat which will rotate vec1 to vec2
 This routine uses only fast geometric transforms, without costly acos/sin
 computations.
 It's exact, fast, and with less degenerate cases than the acos/sin method.
 For an explanation of the math used, you may see for example:
 http://logiciels.cnes.fr/MARMOTTES/marmottes-mathematique.pdf
 @note This is the rotation with shortest angle, which is the one equivalent to
 the
 acos/sin transform method. Other rotations exists, for example to additionally
 keep
 a local horizontal attitude.
 @author Nicolas Brodu
 */
void ofHatQuaternion::makeRotate(const ofHatVec3d &from, const ofHatVec3d &to) {

  // This routine takes any vector as argument but normalized
  // vectors are necessary, if only for computing the dot product.
  // Too bad the API is that generic, it leads to performance loss.
  // Even in the case the 2 vectors are not normalized but same length,
  // the sqrt could be shared, but we have no way to know beforehand
  // at this point, while the caller may know.
  // So, we have to test... in the hope of saving at least a sqrt
  ofHatVec3d sourceVector = from;
  ofHatVec3d targetVector = to;

  double fromLen2 = from.lengthSquared();
  double fromLen;
  // normalize only when necessary, epsilon test
  if ((fromLen2 < 1.0 - 1e-7) || (fromLen2 > 1.0 + 1e-7)) {
    fromLen = sqrt(fromLen2);
    sourceVector /= fromLen;
  } else
    fromLen = 1.0;

  double toLen2 = to.lengthSquared();
  // normalize only when necessary, epsilon test
  if ((toLen2 < 1.0 - 1e-7) || (toLen2 > 1.0 + 1e-7)) {
    double toLen;
    // re-use fromLen for case of mapping 2 vectors of the same length
    if ((toLen2 > fromLen2 - 1e-7) && (toLen2 < fromLen2 + 1e-7)) {
      toLen = fromLen;
    } else
      toLen = sqrt(toLen2);
    targetVector /= toLen;
  }

  // Now let's get into the real stuff
  // Use "dot product plus one" as test as it can be re-used later on
  double dotProdPlus1 = 1.0 + sourceVector.dot(targetVector);

  // Check for degenerate case of full u-turn. Use epsilon for detection
  if (dotProdPlus1 < 1e-7) {

    // Get an orthogonal vector of the given vector
    // in a plane with maximum vector coordinates.
    // Then use it as quaternion axis with pi angle
    // Trick is to realize one value at least is >0.6 for a normalized vector.
    if (fabs(sourceVector.x) < 0.6) {
      const double norm = sqrt(1.0 - sourceVector.x * sourceVector.x);
      _v.x = 0.0;
      _v.y = sourceVector.z / norm;
      _v.z = -sourceVector.y / norm;
      _v.w = 0.0;
    } else if (fabs(sourceVector.y) < 0.6) {
      const double norm = sqrt(1.0 - sourceVector.y * sourceVector.y);
      _v.x = -sourceVector.z / norm;
      _v.y = 0.0;
      _v.z = sourceVector.x / norm;
      _v.w = 0.0;
    } else {
      const double norm = sqrt(1.0 - sourceVector.z * sourceVector.z);
      _v.x = sourceVector.y / norm;
      _v.y = -sourceVector.x / norm;
      _v.z = 0.0;
      _v.w = 0.0;
    }
  }

  else {
    // Find the shortest angle quaternion that transforms normalized vectors
    // into one other. Formula is still valid when vectors are colinear
    const double s = sqrt(0.5 * dotProdPlus1);
    const ofHatVec3d tmp = sourceVector.getCrossed(targetVector) / (2.0 * s);
    _v.x = tmp.x;
    _v.y = tmp.y;
    _v.z = tmp.z;
    _v.w = s;
  }
}

// Make a rotation Quat which will rotate vec1 to vec2
// Generally take adot product to get the angle between these
// and then use a cross product to get the rotation axis
// Watch out for the two special cases of when the vectors
// are co-incident or opposite in direction.
void ofHatQuaternion::makeRotate_original(const ofHatVec3d &from,
                                          const ofHatVec3d &to) {
  const double epsilon = 0.0000001f;

  double length1 = from.length();
  double length2 = to.length();

  // dot product vec1*vec2
  double cosangle = from.dot(to) / (length1 * length2);

  if (fabs(cosangle - 1) < epsilon) {
    // osg::notify(osg::INFO)<<"*** Quat::makeRotate(from,to) with near
    // co-linear vectors, epsilon= "<<fabs(cosangle-1)<<std::endl;

    // cosangle is close to 1, so the vectors are close to being coincident
    // Need to generate an angle of zero with any vector we like
    // We'll choose (1,0,0)
    makeRotate(0.0, 0.0, 0.0, 1.0);
  } else if (fabs(cosangle + 1.0) < epsilon) {
    // vectors are close to being opposite, so will need to find a
    // vector orthongonal to from to rotate about.
    ofHatVec3d tmp;
    if (fabs(from.x) < fabs(from.y))
      if (fabs(from.x) < fabs(from.z))
        tmp.set(1.0, 0.0, 0.0); // use x axis.
      else
        tmp.set(0.0, 0.0, 1.0);
    else if (fabs(from.y) < fabs(from.z))
      tmp.set(0.0, 1.0, 0.0);
    else
      tmp.set(0.0, 0.0, 1.0);

    ofHatVec3d fromd(from.x, from.y, from.z);

    // find orthogonal axis.
    ofHatVec3d axis(fromd.getCrossed(tmp));
    axis.normalize();

    _v.x = axis[0]; // sin of half angle of PI is 1.0.
    _v.y = axis[1]; // sin of half angle of PI is 1.0.
    _v.z = axis[2]; // sin of half angle of PI is 1.0.
    _v.w = 0;       // cos of half angle of PI is zero.

  } else {
    // This is the usual situation - take a cross-product of vec1 and vec2
    // and that is the axis around which to rotate.
    ofHatVec3d axis(from.getCrossed(to));
    double angle = acos(cosangle);
    makeRotate(angle, axis);
  }
}

void ofHatQuaternion::getRotate(double &angle, ofHatVec3d &vec) const {
  double x, y, z;
  getRotate(angle, x, y, z);
  vec.x = x;
  vec.y = y;
  vec.z = z;
}
// Get the angle of rotation and axis of this Quat object.
// Won't give very meaningful results if the Quat is not associated
// with a rotation!
void ofHatQuaternion::getRotate(double &angle, double &x, double &y,
                                double &z) const {
  double sinhalfangle = sqrt(_v.x * _v.x + _v.y * _v.y + _v.z * _v.z);

  angle = 2.0 * atan2(sinhalfangle, _v.w);
  if (sinhalfangle) {
    x = _v.x / sinhalfangle;
    y = _v.y / sinhalfangle;
    z = _v.z / sinhalfangle;
  } else {
    x = 0.0;
    y = 0.0;
    z = 1.0;
  }

  angle = ofHatRadToDeg(angle);
}

/// Spherical Linear Interpolation
/// As t goes from 0 to 1, the Quat object goes from "from" to "to"
/// Reference: Shoemake at SIGGRAPH 89
/// See also
/// http://www.gamasutra.com/features/programming/19980703/quaternions_01.htm
void ofHatQuaternion::slerp(double t, const ofHatQuaternion &from,
                            const ofHatQuaternion &to) {
  const double epsilon = 0.00001;
  double omega, cosomega, sinomega, scale_from, scale_to;

  ofHatQuaternion quatTo(to);
  // this is a dot product

  cosomega = from.asVec4().dot(to.asVec4());

  if (cosomega < 0.0) {
    cosomega = -cosomega;
    quatTo = -to;
  }

  if ((1.0 - cosomega) > epsilon) {
    omega = acos(cosomega); // 0 <= omega <= Pi (see man acos)
    sinomega = sin(omega);  // this sinomega should always be +ve so
    // could try sinomega=sqrt(1-cosomega*cosomega) to avoid a sin()?
    scale_from = sin((1.0 - t) * omega) / sinomega;
    scale_to = sin(t * omega) / sinomega;
  } else {
    /* --------------------------------------------------
     The ends of the vectors are very close
     we can use simple linear interpolation - no need
     to worry about the "spherical" interpolation
     -------------------------------------------------- */
    scale_from = 1.0 - t;
    scale_to = t;
  }

  *this = (from * scale_from) + (quatTo * scale_to);

  // so that we get a Vec4
}

// ref at
// http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/index.htm
ofHatVec3d ofHatQuaternion::getEuler() const {
  double test = x() * y() + z() * w();
  double heading;
  double attitude;
  double bank;
  if (test > 0.499) { // singularity at north pole
    heading = 2 * atan2(x(), w());
    attitude = PI / 2;
    bank = 0;
  } else if (test < -0.499) { // singularity at south pole
    heading = -2 * atan2(x(), w());
    attitude = -PI / 2;
    bank = 0;
  } else {
    double sqx = x() * x();
    double sqy = y() * y();
    double sqz = z() * z();
    heading = atan2(2.0f * y() * w() - 2.0f * x() * z(),
                    1.0f - 2.0f * sqy - 2.0f * sqz);
    attitude = asin(2 * test);
    bank = atan2(2.0f * x() * w() - 2.0f * y() * z(),
                 1.0f - 2.0f * sqx - 2.0f * sqz);
  }

  return ofHatVec3d(ofHatRadToDeg(bank), ofHatRadToDeg(heading),
                    ofHatRadToDeg(attitude));
}

#define QX _v.x
#define QY _v.y
#define QZ _v.z
#define QW _v.w

//----------------------------------------
std::ostream &operator<<(std::ostream &os, const ofHatQuaternion &q) {
  os << q._v.x << ", " << q._v.y << ", " << q._v.z << ", " << q._v.w;
  return os;
}

//----------------------------------------
std::istream &operator>>(std::istream &is, ofHatQuaternion &q) {
  is >> q._v.x;
  is.ignore(2);
  is >> q._v.y;
  is.ignore(2);
  is >> q._v.z;
  is.ignore(2);
  is >> q._v.w;
  return is;
}