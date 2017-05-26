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
      buttons[i]->setup(SPACE_X_RESOLUTION/32*15, SPACE_Y_RESOLUTION/10 * ((6-i) + 0.5) - BUTTONHEIGHT/2, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), (char*)"");
    } else if (i == 3) {
      buttons[i]->setup(SPACE_X_RESOLUTION/32*15, SPACE_Y_RESOLUTION/10 * ((6-i) + 0.5) - BUTTONHEIGHT/2, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), (char*)"");
    }  else {
      buttons[i]->setup(SPACE_X_RESOLUTION/32*15, SPACE_Y_RESOLUTION/10 * ((6-i) + 0.5) - BUTTONHEIGHT/2, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), (char*)"");
    }
  }

  buttons[0]->setText((char*)"Story");
  buttons[0]->setWidth(50*5);
  buttons[0]->setHeight(100);
  
  buttons[1]->setText((char*)"Endless");
  buttons[1]->setWidth(50*7);
  buttons[1]->setHeight(100);
  
  buttons[2]->setText((char*)"Shop");
  buttons[2]->setWidth(50*4);
  buttons[2]->setHeight(100);
  
  buttons[3]->setText((char*)"Highscore");
  buttons[3]->setWidth(50*9);
  buttons[3]->setHeight(100);

  buttons[4]->setText((char*)"Settings");
  buttons[4]->setWidth(50*8);
  buttons[4]->setHeight(100);

  buttons[5]->setText((char*)"Quit");
  buttons[5]->setWidth(50*4);
  buttons[5]->setHeight(100);
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
    type = STORY;
    ended = true;
  }
  if(buttons[1]->Clicked()) {
    type = ENDLESSGAME;
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
 


