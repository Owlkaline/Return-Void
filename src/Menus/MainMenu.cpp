#include "../../include/Menus/MainMenu.h"

MainMenu::MainMenu() {

}

void MainMenu::setup() {
  ended = false;
  type = EXIT;
  
  // Buttons 
  for(int i = 0; i < 6; ++i) {
    buttons.push_back(new Button);
    if(i == 1) {
      buttons[i]->setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/10 * ((6-i) + 0.5) - BUTTONHEIGHT/2, BUTTONWIDTH*2, BUTTONHEIGHT, -1);
    } else if (i == 3) {
      buttons[i]->setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/10 * ((6-i) + 0.5) - BUTTONHEIGHT/2, BUTTONWIDTH*1.5, BUTTONHEIGHT, -1);
    }  else {
      buttons[i]->setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/10 * ((6-i) + 0.5) - BUTTONHEIGHT/2, BUTTONWIDTH, BUTTONHEIGHT, -1);
    }
  }

  buttons[0]->setTexture((char*)"Textures/Menu/MainMenu/Story.png");
  buttons[1]->setTexture((char*)"Textures/Menu/MainMenu/EndlessMode.png");
  buttons[2]->setTexture((char*)"Textures/Menu/MainMenu/Shop.png");
  buttons[3]->setTexture((char*)"Textures/Menu/MainMenu/Highscore.png");
  buttons[4]->setTexture((char*)"Textures/Menu/MainMenu/Settings.png");
  buttons[5]->setTexture((char*)"Textures/Menu/Misc/Quit.png");
  
  background = txt::LoadTexture("Textures/Menu/Background.png");
}

void MainMenu::restart() {

}

void MainMenu::update(float mouseX, float mouseY, float deltaTime, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  if(keyState[ESC] == BUTTON_DOWN && prevKeyState[ESC] != BUTTON_DOWN) {
    prevKeyState[ESC] = keyState[ESC];
    type = EXIT;
    ended = true;
  }
  
  for(unsigned int i = 0; i <  buttons.size(); ++i)
    buttons[i]->update(mouseX, mouseY, mouseBtnState, prevMouseBtnState);
  
  if(buttons[0]->Clicked()) {
    type = GAME;
    ended = true;
  }
  if(buttons[1]->Clicked()) {
    type = SEEDEDGAME;
    ended = true;
  }
  if(buttons[2]->Clicked()) {
    type = SHOP;
    ended = true;
  }
  if(buttons[3]->Clicked()) {
    type = HIGHSCORE;
    ended = true;
  }
  if(buttons[4]->Clicked()) {
    type = SETTINGS;
    ended = true;
  }
  if(buttons[5]->Clicked()) {
    type = EXIT;
    ended = true;
  }  
}
 


