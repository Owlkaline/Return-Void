#include "../../include/Menus/CheckBox.h"

void CheckBox::draw() {
  glEnable(GL_TEXTURE_2D);
  if(isChecked) {
    glBindTexture(GL_TEXTURE_2D, Texture[0]);
  } else {
    glBindTexture(GL_TEXTURE_2D, Texture[1]);
  }
  
  // glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x-width/2, y+height/2, 0.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x+width/2, y+height/2, 0.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x+width/2, y-height/2, 0.0);
    glTexCoord2f(0.0f, 0.0f);     
    glVertex3f(x-width/2, y-height/2, 0.0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void CheckBox::setup(float x, float y) {
  isChecked = false;
  width = 95;
  height = 95;
  this->x = x;
  this->y = y;
  
  Texture[0] = txt::LoadTexture("Textures/Menu/CheckBox.png");
  Texture[1] = txt::LoadTexture("Textures/Menu/CheckBoxChecked.png");
}

void CheckBox::check() { isChecked = true; }
void CheckBox::uncheck() { isChecked = false; }
    
bool CheckBox::getChecked() { return isChecked; }
