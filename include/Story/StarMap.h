#ifndef STARMAP_H 
#define STARMAP_H

#include "../defines.h"

class StarMap {
  public:
    StarMap();
    void draw();
    void update(float mX, float mY, float deltaTime, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);
  protected:
    bool hovered;
};

#endif
