#include "../include/Game.h"

Game::Game() {
  //glutSetCursor(GLUT_CURSOR_NONE);
}

void Game::setup() {
  type = MAINMENU;
  ended = false;
  isNew = true;
  ChRadius = 20;
  ChTexture = txt::LoadTexture("Textures/Game/Crosshair.png");
}

void Game::drawBackground() {

}

void Game::drawCrosshair() { 
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, ChTexture);
  // Nice blue #1e00d5
  glColor3f(0.117647059f, 0, 0.835294197f);
  
  if(ship.getDistanceFromCursor() > MINIMUM_DISTANCETOSHIP) {
    lastChX = ChX;
    lastChY = ChY;
  } else {
    lastChX = ship.getX() +  MINIMUM_DISTANCETOSHIP*ship.getDirectionX();
    lastChY = ship.getY() + MINIMUM_DISTANCETOSHIP*ship.getDirectionY();
   
  }
  
  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(lastChX-ChRadius, lastChY+ChRadius, 0.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(lastChX+ChRadius, lastChY+ChRadius, 0.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(lastChX+ChRadius, lastChY-ChRadius, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(lastChX-ChRadius, lastChY-ChRadius, 0.0);
  glEnd();  
  
  glColor3f(0.0, 0.0, 0.0f);
  glDisable(GL_TEXTURE_2D);
}

void Game::restart() {
  ship.setup();

}

void Game::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  if(isNew) {
    ship.setup();
    isNew = false;
  }
  
  if(keyState[ESC] == BUTTON_DOWN && prevKeyState[ESC] != BUTTON_DOWN) {
    prevKeyState[ESC] = keyState[ESC];
    type = MAINMENU;
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
