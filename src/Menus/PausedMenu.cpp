#include "../../include/Menus/PausedMenu.h"

void PausedMenu::draw() {
  drawBackground();
  Resume.draw();
  Quit.draw();
  lbTitle.draw();
}

void PausedMenu::setup() {

  x = SPACE_X_RESOLUTION/2;
  y = SPACE_Y_RESOLUTION/2;
  width = SPACE_X_RESOLUTION/5;
  height = SPACE_Y_RESOLUTION/3 * 3;

  float width = 247;
  float height = 95;
  Resume.setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/5 * 3, width, height, 0.3);
  Quit.setup(SPACE_X_RESOLUTION/2+width/6, SPACE_Y_RESOLUTION/5 * 2, width, height, 0.3);
  
  lbTitle.setup(SPACE_X_RESOLUTION/2+width/6, SPACE_Y_RESOLUTION/5*4, 0.4);

  std::string str = "Paused";
  lbTitle.setText(str.c_str(), str.length());
  
  // #f08600 R 240 G 134 B 0
  float R = 0.941176471;
  float G = 0.525490246;
  float B = 0;

  lbTitle.setColour(R, G, B);
  
  Resume.setTexture((char*)"Textures/Menu/Resume.png");
  Quit.setTexture((char*)"Textures/Menu/Quit.png");
  Texture = txt::LoadTexture("Textures/Menu/Window.png");
}

void PausedMenu::drawBackground() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Texture);
    glColor4f(1.0, 1.0, 1.0, 0.5);
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(x-width, y+height, 0.0);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(x+width, y+height, 0.0);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(x+width, y-height, 0.0);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(x-width, y-height, 0.0);
    glEnd();    
    glDisable(GL_TEXTURE_2D);
}

void PausedMenu::update(float mouseX, float mouseY, unsigned int* mouseBtnState) {
  paused = true;
  ended = false;
  Resume.update(mouseX, mouseY, mouseBtnState);
  Quit.update(mouseX, mouseY, mouseBtnState);
  
  if(Resume.Clicked()) {
    paused = false;
  }
  if(Quit.Clicked()) {
    ended = true;
  }
}

bool PausedMenu::isPaused() { return paused; }
bool PausedMenu::hasEnded() { return ended; }
