#include "../../include/Story/StarMap.h"

StarMap::StarMap() {
  hovered = false;
}

void StarMap::draw() {
  if(hovered) {
    glColor3f(0.0, 0.0, 1.0);
  } else {
    glColor3f(1.0, 0.0, 0.0);
  }
  drawQuad(SPACE_X_RESOLUTION/2, 50, SPACE_Y_RESOLUTION/2, 50, UP);
}

void StarMap::update(float mX, float mY, float deltaTime, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  if(mX > SPACE_X_RESOLUTION/2-50 && mX < SPACE_X_RESOLUTION/2+50 && mY > SPACE_Y_RESOLUTION/2-50 && mY < SPACE_Y_RESOLUTION/2+50) {
    hovered = true;
  } else {
    hovered = false;
  }
}
