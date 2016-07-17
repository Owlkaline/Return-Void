#include "../../include/Menus/PausedMenu.h"

void PausedMenu::setup() {

  x = SPACE_X_RESOLUTION/2;
  y = SPACE_Y_RESOLUTION/2;
  width = SPACE_X_RESOLUTION/5;
  height = SPACE_Y_RESOLUTION/3 * 3;

  // Resume
  buttons.push_back(new Button);
  buttons[0]->setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/5 * 3, BUTTONWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/GameMenus/Resume.png");
  // Quit
  buttons.push_back(new Button);
  buttons[1]->setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/5 * 2, BUTTONWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/Misc/Quit.png");
  
  lb.push_back(new Label);
  lb[0]->setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/5*4, BUTTONWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/GameMenus/Paused.png");

  Texture = txt::LoadTexture("Textures/Menu/GameMenus/Window.png");
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
    glColor4f(1.0, 1.0, 1.0, 1.0);
}

void PausedMenu::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  paused = true;
  ended = false;
  for(unsigned int i = 0; i < buttons.size(); ++i) {
    buttons[i]->update(mouseX, mouseY, mouseBtnState, prevMouseBtnState);
  }
  // Resume
  if(buttons[0]->Clicked()) {
    paused = false;
  }
  // Quit
  if(buttons[1]->Clicked()) {
    ended = true;
  }
}
void PausedMenu::restart() {}
bool PausedMenu::isPaused() { return paused; }


