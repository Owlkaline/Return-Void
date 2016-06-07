#include "../include/MainMenu.h"

MainMenu::MainMenu() {

}

void MainMenu::setup() {
  ended = false;
  background = txt::LoadTexture("Textures/Menu/Background.png");
}

void MainMenu::drawBackground() {
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
}


void MainMenu::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  if(keyState[ESC] == BUTTON_DOWN && prevKeyState[ESC] != BUTTON_DOWN) {
    prevKeyState[ESC] = keyState[ESC];
    ended = true;
  }
}

void MainMenu::draw() {  
  drawBackground();
}

void MainMenu::restart() {

}

void MainMenu::clean() {

}
