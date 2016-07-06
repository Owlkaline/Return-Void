#include "../../include/GameTypes/SettingsMenu.h"

SettingsMenu::SettingsMenu() {

}

void SettingsMenu::draw() {  
  drawBackground();
  for(int i = 0; i < numOfButtons; ++i)
    buttons[i].draw();
  lbIsRelative.draw();
  lbTrueFalse.draw();
}

void SettingsMenu::clean() {

}

void SettingsMenu::setup() {
  ended = false;
  type = MAINMENU;
  isRelative = false;
  numOfButtons = 3;  
  
  float buttonWidth = 267;
  float buttonHeight = 95;
  float x, y, width, height;
  
  // Return Button
  x = SPACE_X_RESOLUTION/4 + buttonWidth/2;
  y = SPACE_Y_RESOLUTION/10 * (3.5) - buttonHeight/2;
  width = buttonWidth;
  height = buttonHeight;
  buttons[0].setup(x, y, width, height, -1);
  buttons[0].setTexture((char*)"Textures/Menu/Return.png");
  
  // Left Arrow button
  x = SPACE_X_RESOLUTION/4  * 3 - buttonWidth;
  y = SPACE_Y_RESOLUTION/10 * (6.5) - buttonHeight/2;
  width = 50;
  height = buttonHeight;
  buttons[1].setup(x, y, width, height, -1);
  buttons[1].setTexture((char*)"Textures/Menu/LeftArrow.png");
  //buttons[1].setCustomHitBox(x-25, y-buttonHeight/2, x+25, y+buttonHeight/2);
  
  // Right Arrow button
  x = SPACE_X_RESOLUTION/4 * 3 - buttonWidth/4;
  y = SPACE_Y_RESOLUTION/10 * (6.5) - buttonHeight/2;
  width = 50;
  height = buttonHeight;
  buttons[2].setup(x, y, width,height, -1);
  buttons[2].setTexture((char*)"Textures/Menu/RightArrow.png");
  //buttons[2].setCustomHitBox(x-25, y-buttonHeight/2, x+25, y+buttonHeight/2);
   
  // RelitiveMovement Label
  x = SPACE_X_RESOLUTION/4 + buttonWidth;
  y = SPACE_Y_RESOLUTION/10 * (6.5) - buttonHeight/2;
  width = buttonWidth*2;
  height = buttonHeight;
  lbIsRelative.setup(x, y, width, height, (char*)"Textures/Menu/RelativeMovement.png");
  
  buttonWidth = 247;
  // True - False Label
  x = SPACE_X_RESOLUTION/4 * 3 - buttonWidth/2;
  width = buttonWidth;
  height = buttonHeight;
  lbTrueFalse.setup(x, y, width, height, (char*)"Textures/Menu/False.png");
  
  //char* txt = "Start";
  //buttons.setText(txt, 5 );
  //19e8ab R 25 G 232 B 171
  //buttons.setColour(0.098039216, 0.909804008, 0.670588299);
  
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
  
  for(int i = 0; i < numOfButtons; ++i)
    buttons[i].update(mouseX, mouseY, mouseBtnState, prevMouseBtnState);
  
  if(buttons[0].Clicked()) {
    type = MAINMENU;
    ended = true;
  } 
  
  if(buttons[1].Clicked() || buttons[2].Clicked()) {
    if(isRelative) {
      lbTrueFalse.setTexture((char*)"Textures/Menu/False.png"); 
      isRelative = false;
    } else {
      lbTrueFalse.setTexture((char*)"Textures/Menu/True.png"); 
      isRelative = true;
    }
  }
}

void SettingsMenu::drawBackground() {
  // Background
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, background);

  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, SPACE_Y_RESOLUTION, 0.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(SPACE_X_RESOLUTION, SPACE_Y_RESOLUTION, 0.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(SPACE_X_RESOLUTION, 0, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0, 0, 0.0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  
  // Black Box in center
  glColor4f(0.0, 0.0, 0.0f, 0.5f);
  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f((SPACE_X_RESOLUTION/4), (SPACE_Y_RESOLUTION/6) * 4, 0.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f((SPACE_X_RESOLUTION/4)*3, (SPACE_Y_RESOLUTION/6) * 4, 0.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f((SPACE_X_RESOLUTION/4)*3, 0, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(SPACE_X_RESOLUTION/4, 0, 0.0);
  glEnd();
  glColor4f(1.0, 1.0, 1.0f, 1.0f);

}




 


