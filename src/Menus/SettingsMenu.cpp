#include "../../include/Menus/SettingsMenu.h"

SettingsMenu::SettingsMenu() {

}

void SettingsMenu::setup() {
  ended = false;
  type = MAINMENU;
  isRelative = false; 
  
  float buttonWidth = 267; 
  float buttonHeight = 95;
  float x, y, width, height;
  
  // Return Button
  x = SPACE_X_RESOLUTION/8 + buttonWidth/2;
  y = SPACE_Y_RESOLUTION/10 * (2.5) - buttonHeight/2;
  width = buttonWidth;
  height = buttonHeight;
  buttons.push_back(new Button);
  buttons[0]->setup(x, y, width, height, (char*)"Textures/Menu/Return.png");
  
  // Left Arrow button
  x = SPACE_X_RESOLUTION/4  * 3 - buttonWidth;
  y = SPACE_Y_RESOLUTION/10 * (6.5) - buttonHeight/2;
  width = 50;
  height = buttonHeight;
  buttons.push_back(new Button);
  buttons[1]->setup(x, y, width, height, (char*)"Textures/Menu/LeftArrow.png");
  
  // Right Arrow button
  x = SPACE_X_RESOLUTION/4 * 3 - buttonWidth/4;
  y = SPACE_Y_RESOLUTION/10 * (6.5) - buttonHeight/2;
  width = 50;
  height = buttonHeight;
  buttons.push_back(new Button);
  buttons[2]->setup(x, y, width,height, (char*)"Textures/Menu/RightArrow.png");
   
  // RelitiveMovement Label
  x = SPACE_X_RESOLUTION/4 + buttonWidth;
  y = SPACE_Y_RESOLUTION/10 * (6.5) - buttonHeight/2;
  width = buttonWidth*2;
  height = buttonHeight;
  lb.push_back(new Label);
  lb[0]->setup(x, y, width, height, (char*)"Textures/Menu/RelativeMovement.png");
  
  buttonWidth = 247;
  
  // True - False Label
  x = SPACE_X_RESOLUTION/4 * 3 - buttonWidth/2;
  width = buttonWidth;
  height = buttonHeight;
  lb.push_back(new Label);
  lb[1]->setup(x, y, width, height, (char*)"Textures/Menu/False.png");
  
  background = txt::LoadTexture("Textures/Menu/Background.png");
}

void SettingsMenu::restart() {

}

void SettingsMenu::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  if(keyState[ESC] == BUTTON_DOWN && prevKeyState[ESC] != BUTTON_DOWN) {
    prevKeyState[ESC] = keyState[ESC];
    type = MAINMENU;
    ended = true;
  }
  
  for(unsigned int i = 0; i < buttons.size(); ++i)
    buttons[i]->update(mouseX, mouseY, mouseBtnState, prevMouseBtnState);
  
  if(buttons[0]->Clicked()) {
    type = MAINMENU;
    ended = true;
  } 
  
  if(buttons[1]->Clicked() || buttons[2]->Clicked()) {
    if(isRelative) {
      lb[1]->setTexture((char*)"Textures/Menu/False.png"); 
      isRelative = false;
    } else {
      lb[1]->setTexture((char*)"Textures/Menu/True.png"); 
      isRelative = true;
    }
  }
}


