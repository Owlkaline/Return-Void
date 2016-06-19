#include "../../include/GameTypes/SettingsMenu.h"

SettingsMenu::SettingsMenu() {

}

void SettingsMenu::draw() {  
  drawBackground();
  
  for(int i = 0; i < numOfButtons; ++i)
    buttons[i].draw();
  
  checkBox.draw();
  drawCursor();
}

void SettingsMenu::clean() {

}

void SettingsMenu::setup() {
  ended = false;
  cursorRadius = 20;
  type = MAINMENU;
  numOfButtons = 2;
  
  // Buttons
  float buttonWidth = 247;
  float buttonHeight = 95;
 
    buttons[0].setup(SPACE_X_RESOLUTION/4 + buttonWidth/2, SPACE_Y_RESOLUTION/10 * (6.5) - buttonHeight/2, buttonWidth, buttonHeight, -1);
  
   buttonWidth = 267;
   buttons[1].setup(SPACE_X_RESOLUTION/4 + buttonWidth/2, SPACE_Y_RESOLUTION/10 * (3.5) - buttonHeight/2, buttonWidth, buttonHeight, -1);

  buttons[0].setTexture((char*)"Textures/Menu/GameMode.png");

  buttons[1].setTexture((char*)"Textures/Menu/Return.png");
  
  checkBox.setup((SPACE_X_RESOLUTION/4)*3 - 50, SPACE_Y_RESOLUTION/10 * (6.2));

  
  //char* txt = "Start";
  //buttons.setText(txt, 5 );
  //19e8ab R 25 G 232 B 171
  //buttons.setColour(0.098039216, 0.909804008, 0.670588299);
  
  background = txt::LoadTexture("Textures/Menu/Background.png");
  cursorTexture = txt::LoadTexture("Textures/Game/Crosshair.png");
}

void SettingsMenu::restart() {

}

void SettingsMenu::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  if(keyState[ESC] == BUTTON_DOWN && prevKeyState[ESC] != BUTTON_DOWN) {
    prevKeyState[ESC] = keyState[ESC];
    type = MAINMENU;
    ended = true;
  }
  cursorX = mouseX;
  cursorY = mouseY;
  
  for(int i = 0; i < numOfButtons; ++i)
    buttons[i].update(mouseX, mouseY, mouseBtnState, prevMouseBtnState);
  
  if(buttons[0].Clicked()) {
    if(checkBox.getChecked()) {
      checkBox.uncheck();
    } else {
      checkBox.check();
    }
  }
  if(buttons[1].Clicked()) {
    type = MAINMENU;
    ended = true;
  } 
}

void SettingsMenu::drawCursor() { 
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, cursorTexture);
  // Nice blue #1e00d5
  glColor3f(0.117647059f, 0, 0.835294197f);
  
  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(cursorX-cursorRadius, cursorY+cursorRadius, 0.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(cursorX+cursorRadius, cursorY+cursorRadius, 0.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(cursorX+cursorRadius, cursorY-cursorRadius, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(cursorX-cursorRadius, cursorY-cursorRadius, 0.0);
  glEnd();  
  
  glColor3f(0.0, 0.0, 0.0f);
  glDisable(GL_TEXTURE_2D);
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




 

