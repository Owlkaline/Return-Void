#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <math.h>
#include "../defines.h"

namespace move {
  void fall(float* y, float speed, float* movementAngle, bool *visible);
  void semicircle(float *x, float *y, float width, float height, float speed, float startX, float startY, float* movementAngle, bool* isOnRightSide, bool* hasFinished, bool* visible, int numOfBullets);
  void sinwave(float *x, float *y, float* movementAngle, float height, float speed, float amp, float startX, bool* visible);
  void sidefall(float* x, float* y, float width, float* startX, float* startY, float speed, float* angle, int* cycle);
}

#endif
