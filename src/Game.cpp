#include "../include/Game.h"

Game::Game() {
  ended = false;
  isNew = true;
  ChRadius = 20;
  ChTexture = txt::LoadTexture("Textures/Game/Crosshair.png");
  //glutSetCursor(GLUT_CURSOR_NONE);
}

void Game::drawBackground() {

}

void Game::drawCrosshair() { 
  glBindTexture(GL_TEXTURE_2D, ChTexture);
  // Nice blue #1e00d5
  glColor3f(0.117647059f, 0, 0.835294197f);
  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(ChX-ChRadius, ChY+ChRadius, 0.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(ChX+ChRadius, ChY+ChRadius, 0.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(ChX+ChRadius, ChY-ChRadius, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(ChX-ChRadius, ChY-ChRadius, 0.0);
  glEnd();
  glColor3f(1.0, 1.0, 1.0f);
  glDisable(GL_TEXTURE_2D);
}

void Game::restart() {

}

void Game::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  if(isNew) {
    ship.setup();
    isNew = false;
  }
  
  if(keyState[ESC] == BUTTON_DOWN && prevKeyState[ESC] != BUTTON_DOWN) {
    prevKeyState[ESC] = keyState[ESC];
    ended = true;
  }
  
  ChX = mouseX;
  ChY = mouseY;
  ship.update(mouseX, mouseY, mouseBtnState, keyState, prevKeyState);
}

void Game::draw() {  
  drawBackground();
  ship.draw();
  drawCrosshair();
  
}

void Game::clean() {

}
