#include "../../include/Drops/Shield.h"

Shield::Shield() {
  tick = 100;
}

void Shield::draw() {
  if(!isCollected) {
    glEnable(GL_TEXTURE_2D);  
    
    glBindTexture(GL_TEXTURE_2D, getShieldTexture());
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
  } else {
    lbTitle.draw();
  }
  
}

void Shield::setup(float x, float y) {
  this->x = x;
  this->y = y;
  width = 35;
  height = 45;
  visible = true;
  isCollected = false;

  lbTitle.setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 0.2, true);
  lbTitle.setColour( 0.5,  0.5,  0.1);
  lbTitle.setText("Shield", 6);  
}

void Shield::update() {
  tick++;
  if(!isCollected) {
    y-=3 * tick/100.0;
  } else {
    lbTitle.update();
    if(lbTitle.timeExpired())
      visible = false;
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

int Shield::getType() {
  //visible = false;
  isCollected = true;
  lbTitle.setX(x);
  lbTitle.setY(y);  
  lbTitle.setTimer(20);
  return SHIELD;
}
