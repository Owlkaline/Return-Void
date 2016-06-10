#include "../include/MainMenu.h"

MainMenu::MainMenu() {

}

void MainMenu::setup() {
  ended = false;
  cursorRadius = 20;
  type = EXIT;
  //Button

  float buttonWidth = 140;
  float buttonHeight = 35;
  buttons[0].setup(SPACE_X_RESOLUTION/4 + buttonWidth, SPACE_Y_RESOLUTION/10 * 6.5-buttonHeight, buttonWidth, buttonHeight);
  buttonWidth = 145;
  buttonHeight = 45;
  buttons[1].setup(SPACE_X_RESOLUTION/4 + buttonWidth, SPACE_Y_RESOLUTION/10 * 5.5-buttonHeight, buttonWidth, buttonHeight);
  buttonWidth = 145;
  buttonHeight = 45;
  buttons[2].setup(SPACE_X_RESOLUTION/4 + buttonWidth, SPACE_Y_RESOLUTION/10 * 4.5-buttonHeight, buttonWidth, buttonHeight);
  buttonWidth = 145;
  buttonHeight = 45;
  buttons[3].setup(SPACE_X_RESOLUTION/4 + buttonWidth, SPACE_Y_RESOLUTION/10 * 3.5-buttonHeight, buttonWidth, buttonHeight);
  
  buttons[0].setTexture((char*)"Textures/Menu/Start.png");
  buttons[1].setTexture((char*)"Textures/Menu/Seed.png");
  buttons[2].setTexture((char*)"Textures/Menu/Settings.png");
  buttons[3].setTexture((char*)"Textures/Menu/Quit.png");
  numOfButtons = 4;
  //char* txt = "Start";
  //buttons.setText(txt, 5 );
  //19e8ab R 25 G 232 B 171
  //buttons.setColour(0.098039216, 0.909804008, 0.670588299);
  background = txt::LoadTexture("Textures/Menu/Background.png");
  cursorTexture = txt::LoadTexture("Textures/Game/Crosshair.png");
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
    //glColor3f(0.0, 0.0, 0.0f);
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
  //glColor3f(1.0, 1.0, 1.0f);
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

void MainMenu::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  if(keyState[ESC] == BUTTON_DOWN && prevKeyState[ESC] != BUTTON_DOWN) {
    prevKeyState[ESC] = keyState[ESC];
    type = EXIT;
    ended = true;
  }
  cursorX = mouseX;
  cursorY = mouseY;
  
  for(int i = 0; i < numOfButtons; ++i)
    buttons[i].update(mouseX, mouseY, mouseBtnState);
  
  if(buttons[0].checkIfClicked()) {
    type = GAME;
    ended = true;
  }
  if(buttons[1].checkIfClicked()) {
    type = SEEDEDGAME;
    ended = true;
  }
  if(buttons[2].checkIfClicked()) {
    //type = SETTINGS;
    //ended = true;
  }
  if(buttons[3].checkIfClicked()) {
    type = EXIT;
    ended = true;
  }
  
}

void MainMenu::draw() {  
  drawBackground();
  
  for(int i = 0; i < numOfButtons; ++i)
    buttons[i].draw();
  
  drawCursor();
}
 
void MainMenu::restart() {

}

void MainMenu::clean() {

}
