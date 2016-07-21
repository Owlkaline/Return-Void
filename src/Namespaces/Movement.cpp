#include "../../include/Namespaces/Movement.h"

void move::fall(float* y, float speed, float* movementAngle, bool* visible) {
  *y-=speed;
  movementAngle = 0;
  if(*y <= -75)
    *visible = false;
}

void move::semicircle(float *x, float *y, float width, float height, float speed, float startX, float *startY, float* movementAngle, bool* isOnRightSide, int* cycle, bool* visible, int numOfBullets) {
  switch(*cycle) {
    case 0:
      *y-=speed;
      if(*y <= (height * cos(((2*M_PI)/800)*(*x)) + SPACE_Y_RESOLUTION-height)) {
        *cycle+=1;
        *y = (height * cos(((2*M_PI)/800)*(*x)) + SPACE_Y_RESOLUTION-height);
        *startY = SPACE_Y_RESOLUTION-height;
      }
      break;
    case 1:
      if(*isOnRightSide) {
        *x-=speed;
        *y = (height * cos(((2*M_PI)/800)*(*x)) + *startY);
        if(*x < SPACE_X_RESOLUTION/8)
          *cycle+=1;
      } else {
        *x+=speed;
        *y = (height * cos(((2*M_PI)/800)*(*x)) + *startY);
        if(*x > SPACE_X_RESOLUTION/8*7)
          *cycle+=1;
      }

      break;
    case 2:
      if(*isOnRightSide) {
        *x+=speed;
        *y = (height * cos(((2*M_PI)/800)*(*x)) + SPACE_Y_RESOLUTION-height);
        if(*x > SPACE_X_RESOLUTION/8*7)
          *cycle+=1;
      } else {
        *x-=speed;
        *y = (height * cos(((2*M_PI)/800)*(*x)) + SPACE_Y_RESOLUTION-height);
        if(*x < SPACE_X_RESOLUTION/8)
          *cycle+=1;
      }
      break;
    case 3:
      *y+=speed;
      if(*y > SPACE_Y_RESOLUTION+height)
        *visible = false;
      break;
  }
}

void move::sinwave(float *x, float *y, float* movementAngle, float height, float speed, float amp, float startX, bool* visible) {
  *y-=speed;
  *x = amp * sin(((2*M_PI)/800)*(*y)) + startX;
  *movementAngle = 0;
  if(*y <= -height)
    *visible = false;
}


void move::sidefall(float* x, float* y, float width, float height, float* startX, float* startY, float speed, float* angle, int* cycle, bool* visible) {
  float rad = 0;
  switch(*cycle) {
    case 0: // Fall Down Right side
      if(*y > SPACE_Y_RESOLUTION/2) {
        *y-=speed;
        *x = SPACE_X_RESOLUTION-width/2;
      } else {
        *startX = *x - SPACE_X_RESOLUTION/8;
        *startY = *y;
        *cycle+=1;
      }
      break;
    case 1: // Big Semi circle a cross screen right to left
      *angle+=speed/5.0;      
      rad = *angle * M_PI/180.0;
      *x = *startX + cos(-rad) * (SPACE_X_RESOLUTION/8);
      *y = *startY + sin(-rad) * (SPACE_X_RESOLUTION/8);
      if(*angle >= 170 && *y >= SPACE_Y_RESOLUTION/2) {
        *cycle+=1;
        *angle = 0;
        *startX = *x - SPACE_X_RESOLUTION/4 - width*2;
        *startY = SPACE_Y_RESOLUTION/2;
      }
      break;
    case 2: // Small Semi circle on left side
      *angle+=speed/10;//0.5;//speed/5;      
      rad = *angle * M_PI/180.0;
      *x = *startX + cos(rad) * (SPACE_Y_RESOLUTION/2);
      *y = *startY + sin(rad) * (SPACE_Y_RESOLUTION/2);
      if(*angle >= 150 && *y <= SPACE_Y_RESOLUTION/2) {
        *angle = 0;
        *startX = *x - SPACE_X_RESOLUTION/10 + width*2;
        *startY = SPACE_Y_RESOLUTION/2;
        *cycle += 1;
      }
      break;
    case 3:
      *angle+=speed/5.0*2; //1.5;//speed/5;      
      rad = *angle * M_PI/180.0;
      *x = *startX + cos(-rad) * (SPACE_X_RESOLUTION/14);
      *y = *startY + sin(-rad) * (SPACE_X_RESOLUTION/14);
      if(*angle >= 170) {
        *cycle += 1;
      }
      break;
    case 4:
      *y+=speed;
      if(*y > SPACE_Y_RESOLUTION+height)
        *visible = false;
      break;
  }
}

void move::AlphaOne(float* x, float* y, float width, float height, float speed, int* cycle) {
  switch(*cycle) {
    case 0:
      *y -= speed;
      *x = SPACE_X_RESOLUTION/2;
      if(*y < SPACE_Y_RESOLUTION-height/2)
        *cycle += 1;
      break;
    case 1:
      *x-=speed;
      if(*x <= width/2+2)
        *cycle+=1;
      break;
    case 2:
      *x+=speed;
      if(*x >= SPACE_X_RESOLUTION-width/2)
        *cycle-=1;
      break;
  }
}
