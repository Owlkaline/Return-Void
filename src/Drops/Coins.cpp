#include "../../include/Drops/Coins.h"

Coins::Coins() {
  tick = 100;
}

void Coins::draw() {
  if(!isCollected) {
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
  } else {
    lbTitle.draw();
  }
}

void Coins::setup(float x, float y) {
  this->x = x;
  this->y = y;
  width = 50;
  height = 50;
  visible = true;
  lbTitle.setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 0.2, true);
  lbTitle.setColour( 0.5,  0.5,  0.1);
  lbTitle.setText("Coins", 5);  
}

void Coins::update() {
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

int Coins::getType() {
  isCollected = true;
  lbTitle.setX(x);
  lbTitle.setY(y);  
  lbTitle.setTimer(20);
  return COIN;
}
