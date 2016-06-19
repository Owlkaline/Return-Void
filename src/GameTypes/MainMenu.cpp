#include "../../include/GameTypes/MainMenu.h"

MainMenu::MainMenu() {

}

void MainMenu::draw() {  
  drawBackground();
  
  for(int i = 0; i < numOfButtons; ++i)
    buttons[i].draw();
  
  drawCursor();
}

void MainMenu::clean() {

}

void MainMenu::setup() {
  ended = false;
  cursorRadius = 20;
  type = EXIT;
  numOfButtons = 5;
  
  // Buttons
  float buttonWidth = 247;
  float buttonHeight = 95;
  for(int i = 0; i < numOfButtons; ++i) {
    if(i == 1) {
      buttons[1].setup(SPACE_X_RESOLUTION/4 + buttonWidth/4*3.4, SPACE_Y_RESOLUTION/10 * ((6-i) + 0.5) - buttonHeight/2, buttonWidth*1.7, buttonHeight, -1);
    } else {
      buttons[i].setup(SPACE_X_RESOLUTION/4 + buttonWidth/2, SPACE_Y_RESOLUTION/10 * ((6-i) + 0.5) - buttonHeight/2, buttonWidth, buttonHeight, -1);
    }
  }

  buttons[0].setTexture((char*)"Textures/Menu/Story.png");
  buttons[1].setTexture((char*)"Textures/Menu/EndlessMode.png");
  buttons[2].setTexture((char*)"Textures/Menu/Shop.png");
  buttons[3].setTexture((char*)"Textures/Menu/Settings.png");
  buttons[4].setTexture((char*)"Textures/Menu/Quit.png");

  //char* txt = "Start";
  //buttons.setText(txt, 5 );
  //19e8ab R 25 G 232 B 171
  //buttons.setColour(0.098039216, 0.909804008, 0.670588299);
  
  background = txt::LoadTexture("Textures/Menu/Background.png");
  cursorTexture = txt::LoadTexture("Textures/Game/Crosshair.png");
}

void MainMenu::restart() {

}

void MainMenu::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  if(keyState[ESC] == BUTTON_DOWN && prevKeyState[ESC] != BUTTON_DOWN) {
    prevKeyState[ESC] = keyState[ESC];
    type = EXIT;
    ended = true;
  }
  cursorX = mouseX;
  cursorY = mouseY;
  
  for(int i = 0; i < numOfButtons; ++i)
    buttons[i].update(mouseX, mouseY, mouseBtnState, prevMouseBtnState);
  
  if(buttons[0].Clicked()) {
    type = GAME;
    ended = true;
  }
  if(buttons[1].Clicked()) {
    type = SEEDEDGAME;
    ended = true;
  }
  if(buttons[2].Clicked()) {

  }
  if(buttons[3].Clicked()) {
    type = SETTINGS;
    ended = true;
  }
  if(buttons[4].Clicked()) {
    type = EXIT;
    ended = true;
  }  
}

void MainMenu::drawCursor() { 
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

void MainMenu::drawBackground() {
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




 


