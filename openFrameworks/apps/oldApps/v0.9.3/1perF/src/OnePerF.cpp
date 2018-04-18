//
//  OnePerF.cpp
//  1perF
//

#include "OnePerF.hpp"

float OnePerF::calc() {

  randFloat = (float)rand() / RAND_MAX;

  if (randFloat < 0.5) {
    lightPercent = randFloat + 2 * randFloat * randFloat;
  } else {
    lightPercent = randFloat - 2 * (1 - randFloat) * (1 - randFloat);
  }

  if (lightPercent < 0.2) {
    lightPercent += 0.2;
  }

  return lightPercent;
}