#include "../../include/Namespaces/Movement.h"

void move::fall(float* y, float speed, float* movementAngle, bool* visible) {
  *y-=speed;
  movementAngle = 0;
  if(*y <= -75)
    *visible = false;
}

void move::semicircle(float *x, float *y, float width, float height, float speed, float startX, float startY, float* movementAngle, bool* isOnRightSide, bool* hasFinished, bool* visible, int numOfBullets) {
  if(*y < SPACE_Y_RESOLUTION+height) {
    if(!*isOnRightSide) {
      *movementAngle+=speed/10;
      *x = SPACE_X_RESOLUTION/2 + cos(*movementAngle/ 180.0f * (float)M_PI) * startX;
      *y = SPACE_Y_RESOLUTION + sin(*movementAngle/ 180.0f * (float)M_PI) * SPACE_Y_RESOLUTION/2+height;
    } else {
      *movementAngle-=speed/10;
      *x = SPACE_X_RESOLUTION/2 + cos(*movementAngle/ 180.0f * (float)M_PI) * -startX;
      *y = SPACE_Y_RESOLUTION + sin(*movementAngle/ 180.0f * (float)M_PI) * -SPACE_Y_RESOLUTION/2+height;
    }
    *hasFinished = true;
   } else {
     if(!*hasFinished) {
       *y-=speed;
     } else if(numOfBullets <= 0) {
       *visible = false;
     }
   }
}

void move::sinwave(float *x, float *y, float* movementAngle, float height, float speed, float amp, float startX, bool* visible) {
  *y-=speed;
  *x = amp * sin(((2*M_PI)/800)*(*y)) + startX;
  *movementAngle = 0;
  if(*y <= -height)
    *visible = false;
}

void move::sidefall(float* x, float* y, float width, float* startX, float* startY, float speed, float* angle, int* cycle) {
  switch(*cycle) {
    case 0:
      if(*y > SPACE_Y_RESOLUTION/2) {
        *y-=speed;
        *x = SPACE_X_RESOLUTION-width/2;
      } else {
        *startX = *x - SPACE_X_RESOLUTION/8;
        *startY = *y;
        *cycle+=1;
      }
      break;
    case 1:
      *angle+=1;
      float rad = *angle * M_PI/180.0;
      *x = *startX + cos(-rad) * (SPACE_X_RESOLUTION/8);
      *y = *startY + sin(-rad) * (SPACE_X_RESOLUTION/8);
      break;
  }
}
