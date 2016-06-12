#include "../../include/Menus/Button.h"

Button::Button() {

}

void Button::draw() {
  if(hasTexture) {
    if(hasBeenClicked) {
      glColor3f(0.0f, 0.0f, 0.0f);
    } else if(isSelected) {
      glColor3f(0.5f, 0.5f, 0.5f);
    } else {
      glColor3f(1.0, 1.0, 1.0);
    }
  
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Texture);
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
  if(scale != -1)
    lbTitle.draw();
  
  //drawChar();
}

void Button::clean() {

}

void Button::setup(float x, float y, float width, float height, float scale) {
  isSelected = false;
  hasTexture = false;
  hasBeenClicked = false;
  usingCustomHitBox = false;
  
  this->x = x;
  this->y = y;
  this->scale = scale;
  this->width = width;
  this->height = height;
  lbTitle.setup(x, y, scale);
}

void Button::update(float mouseX, float mouseY, unsigned int* mouseBtnState) {
  hasBeenClicked = false;
  isSelected = false;
  if(!usingCustomHitBox) {
    if(mouseY > y-height/2 && mouseY < y+height/2) {
      isSelected = true;
      if(mouseBtnState[GLUT_LEFT_BUTTON] == BUTTON_DOWN) {
        hasBeenClicked = true;
      }
    }
  } else {
    if(mouseY > customHitBox[2] && mouseY < customHitBox[3]) {
      hasBeenClicked = true;
    }
  }
}

void Button::setTexture(char* filename) {
  Texture = txt::LoadTexture(filename);
  hasTexture = true;
}

void Button::setText(const char* str, int length) {
  lbTitle.setText(str, length);
}

void Button::setColour(float R, float G, float B) {
  lbTitle.setColour(R, G, B);
}

bool Button::Clicked() {
  return hasBeenClicked;
}

void Button::setCustomHitBox(float x1, float y1, float x2, float y2) {
  usingCustomHitBox = true;
  customHitBox[0] = x1;
  customHitBox[1] = y1;
  customHitBox[2] = x2;
  customHitBox[3] = y2;
}


