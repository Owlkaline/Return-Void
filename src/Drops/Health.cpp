#include "../../include/Drops/Health.h"

Health::Health() {
  tick = 100;
}

void Health::draw() {
  if(!isCollected) {
    glEnable(GL_TEXTURE_2D);  
    
    glBindTexture(GL_TEXTURE_2D, getHealthTexture());
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
}

void Health::setup(float x, float y) {
  this->x = x;
  this->y = y;
  width = 50;
  height = 50;
  visible = true;
  isCollected = false;
  name = "Health";
}

void Health::update() {
  tick++;
  
  if(!isCollected) {
    y-=3 * tick/100.0;  
  }
  
  if(y < 0 - height)
    visible = false;
  if(y > SPACE_Y_RESOLUTION+height)
    visible = false;
  if(x < -width) 
    visible = false;
  if(x > SPACE_X_RESOLUTION+width)
    visible = false;
} 

int Health::getType() {
  isCollected = true;
  return HEALTH;
}
