#include "../../include/Menus/SettingsMenu.h"

SettingsMenu::SettingsMenu() {

}

void SettingsMenu::setup() {
  settings.Load();
  ended = false;
  type = MAINMENU;
  if(settings.getRelativeMovement() == 1) {
    isRelative = true;
  } else {
    isRelative = false;
  } 
  
  // Return Button
  x = SPACE_X_RESOLUTION/4 + BUTTONWIDTH/2;
  y = SPACE_Y_RESOLUTION/10 * (1.0) - BUTTONHEIGHT/2;
  buttons.push_back(new Button);
  buttons[0]->setup(x, y, BUTTONWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/Misc/Return.png");
  
  // Save Button
  x = SPACE_X_RESOLUTION/4*2.5 + BUTTONWIDTH/2;
  y = SPACE_Y_RESOLUTION/10 * (1.0) - BUTTONHEIGHT/2;
  buttons.push_back(new Button);
  buttons[1]->setup(x, y, BUTTONWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/SettingsMenu/Save.png");
  
  // Left Arrow button
  x = SPACE_X_RESOLUTION/4  * 3 - BUTTONWIDTH - ARROWWIDTH/2;
  y = SPACE_Y_RESOLUTION/10 * (6.5) - BUTTONHEIGHT/2;
  buttons.push_back(new Button);
  buttons[2]->setup(x, y, ARROWWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/Misc/LeftArrow.png");
  
  // Right Arrow button
  x = SPACE_X_RESOLUTION/4 * 3 - ARROWWIDTH/2;
  y = SPACE_Y_RESOLUTION/10 * (6.5) - BUTTONHEIGHT/2;
  buttons.push_back(new Button);
  buttons[3]->setup(x, y, ARROWWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/Misc/RightArrow.png");
   
  // RelitiveMovement Label
  x = SPACE_X_RESOLUTION/4 + BUTTONWIDTH*1.25;
  y = SPACE_Y_RESOLUTION/10 * (6.5) - BUTTONHEIGHT/2;
  lb.push_back(new Label);
  lb[0]->setup(x, y, BUTTONWIDTH*2.5, BUTTONHEIGHT, (char*)"Textures/Menu/SettingsMenu/RelativeMovement.png");

  // True - False Label
  x = SPACE_X_RESOLUTION/4 * 3 - BUTTONWIDTH/2 - ARROWWIDTH/2;
  lb.push_back(new Label);
  if(isRelative) {
    lb[1]->setup(x, y, BUTTONWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/Misc/True.png");
  } else {
    lb[1]->setup(x, y, BUTTONWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/Misc/False.png");
  }
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
  
  if(buttons[1]->Clicked()) {
    settings.setRelativeMovement(isRelative);
    settings.Save();
  }
  
  if(buttons[2]->Clicked() || buttons[3]->Clicked()) {
    if(isRelative) {
      lb[1]->setTexture((char*)"Textures/Menu/Misc/False.png"); 
      isRelative = false;
    } else {
      lb[1]->setTexture((char*)"Textures/Menu/Misc/True.png"); 
      isRelative = true;
    }
  }
}


