#ifndef MOVEMENT_H
#define MOVEMENT_H

#define _USE_MATH_DEFINES
#include <math.h>
#include "../defines.h"

namespace move {
  void fall(float* y, float speed, float* movementAngle, bool *visible);
  void AlphaOne(float* x, float* y, float width, float height, float speed, int* cycle);
  void sidefall(float* x, float* y, float width, float height, float* startX, float* startY, float speed, float* angle, int* cycle, bool* visible);  
  void sinwave(float *x, float *y, float* movementAngle, float height, float speed, float amp, float startX, bool* visible);
  void semicircle(float *x, float *y, float width, float height, float speed, float startX, float *startY, float* movementAngle, bool* isOnRightSide, int* cycle, bool* visible, int numOfBullets);
}

#endif
