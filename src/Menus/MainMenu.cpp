#include "../../include/Menus/MainMenu.h"

MainMenu::MainMenu() {

}

void MainMenu::setup() {
  ended = false;
  type = EXIT;
  
  // Buttons 
  float buttonWidth = 247;
  float buttonHeight = 95;
  for(int i = 0; i < 5; ++i) {
    buttons.push_back(new Button);
    if(i == 1) {
      buttons[1]->setup(SPACE_X_RESOLUTION/4 + buttonWidth/4*3.4, SPACE_Y_RESOLUTION/10 * ((6-i) + 0.5) - buttonHeight/2, buttonWidth*1.7, buttonHeight, -1);
    } else {      
      buttons[i]->setup(SPACE_X_RESOLUTION/4 + buttonWidth/2, SPACE_Y_RESOLUTION/10 * ((6-i) + 0.5) - buttonHeight/2, buttonWidth, buttonHeight, -1);
    }
  }

  buttons[0]->setTexture((char*)"Textures/Menu/MainMenu/Story.png");
  buttons[1]->setTexture((char*)"Textures/Menu/MainMenu/EndlessMode.png");
  buttons[2]->setTexture((char*)"Textures/Menu/MainMenu/Shop.png");
  buttons[3]->setTexture((char*)"Textures/Menu/MainMenu/Settings.png");
  buttons[4]->setTexture((char*)"Textures/Menu/Misc/Quit.png");

  //char* txt = "Start";
  //buttons.setText(txt, 5 );
  //19e8ab R 25 G 232 B 171
  //buttons.setColour(0.098039216, 0.909804008, 0.670588299);
  
  background = txt::LoadTexture("Textures/Menu/Background.png");
}

void MainMenu::restart() {

}

void MainMenu::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  if(keyState[ESC] == BUTTON_DOWN && prevKeyState[ESC] != BUTTON_DOWN) {
    prevKeyState[ESC] = keyState[ESC];
    type = EXIT;
    ended = true;
  }
  
  for(unsigned int i = 0; i <  buttons.size(); ++i)
    buttons[i]->update(mouseX, mouseY, mouseBtnState, prevMouseBtnState);
  
  if(buttons[0]->Clicked()) {
    type = SEEDEDGAME;
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
    type = SETTINGS;
    ended = true;
  }
  if(buttons[4]->Clicked()) {
    type = EXIT;
    ended = true;
  }  
}
 


