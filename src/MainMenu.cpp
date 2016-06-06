#include "../include/MainMenu.h"

MainMenu::MainMenu() {
  ended = false;
}

void MainMenu::drawBackground() {
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_QUADS);
    glVertex3f(0, 100, 0.0);
    glVertex3f(100, 100, 0.0);
    glVertex3f(100, 0, 0.0);
    glVertex3f(0, 0, 0.0);
  glEnd();
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
