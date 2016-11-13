#include "../../include/GameTypes/Story.h"

void Story::draw() {
  world.draw();
}

void Story::setup() {

}

void Story::update(float mX, float mY, float deltaTime, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {

  world.update(mX, mY, deltaTime, mouseBtnState, prevMouseBtnState, keyState, prevKeyState);

  if(keyState[ESC] == BUTTON_DOWN && prevKeyState[ESC] != BUTTON_DOWN) {
    prevKeyState[ESC] = keyState[ESC];
    type = MAINMENU;
    ended = true;
    printf("Returning to Menu, from story starmap\n");
  }
}
    
void Story::restart() {
        
}
