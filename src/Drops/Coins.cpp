#include "../../include/Drops/Coins.h"

Coins::Coins() {

}

void Coins::draw() {
  glEnable(GL_TEXTURE_2D);  
    
  glBindTexture(GL_TEXTURE_2D, getCoinTexture());
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

void Coins::setup(float x, float y) {

  this->x = x;
  this->y = y;
  width = 50;
  height = 50;
  visible = true;

}

void Coins::update() {
  y-=3;
  if(y < 0 - height)
    visible = false;
 // if(y > SPACE_Y_RESOLUTION+height)
 //   visible = false;
  if(x < -width) 
    visible = false;
  if(x > SPACE_X_RESOLUTION+width)
    visible = false;
}
