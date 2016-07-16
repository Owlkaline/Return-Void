#include "../../include/Menus/Shop.h"

Shop::Shop() {

}

void Shop::setup() {
  ended = false;
  type = MAINMENU;
  
  // Buttons
  float buttonWidth = 247;
  float buttonHeight = 95;
 
   buttons.push_back(new Button);
   buttons[0]->setup(SPACE_X_RESOLUTION/4 + buttonWidth/2, SPACE_Y_RESOLUTION/10 * (6.5) - buttonHeight/2, buttonWidth, buttonHeight, (char*)"Textures/Menu/GameMode.png");
  
   buttonWidth = 267;
   buttons.push_back(new Button);
   buttons[1]->setup(SPACE_X_RESOLUTION/4 + buttonWidth/2, SPACE_Y_RESOLUTION/10 * (3.5) - buttonHeight/2, buttonWidth, buttonHeight, (char*)"Textures/Menu/Return.png");
  
  checkbox.push_back(new CheckBox);
  checkbox[0]->setup((SPACE_X_RESOLUTION/4)*3 - 50, SPACE_Y_RESOLUTION/10 * (6.2));
  
  background = txt::LoadTexture("Textures/Menu/Background.png");
}

void Shop::restart() {

}

void Shop::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  if(keyState[ESC] == BUTTON_DOWN && prevKeyState[ESC] != BUTTON_DOWN) {
    prevKeyState[ESC] = keyState[ESC];
    type = MAINMENU;
    ended = true;
  }

  for(unsigned int i = 0; i < buttons.size(); ++i)
    buttons[i]->update(mouseX, mouseY, mouseBtnState, prevMouseBtnState);
  
  if(buttons[0]->Clicked()) {
    
  }
  if(buttons[1]->Clicked()) {
    type = MAINMENU;
    ended = true;
  } 
}




 


