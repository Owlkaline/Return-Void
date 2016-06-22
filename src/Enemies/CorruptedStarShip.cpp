#include "../../include/Enemies/CorruptedStarShip.h"

void CorruptedStarShip::setup(float drop) {
  speed = 3;
  width = 75;
  height = 75;
  health = 15;
  maxHealth = health;
  tick = 0;
  visible = true;
  maxWeaponMounts = 1;
  x = -SPACE_X_RESOLUTION;
  y = -SPACE_X_RESOLUTION;

  wasKilled = false;
  
  this->drop = drop; 

  score = 30;
  lbScore.setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 0.2, true);
  lbScore.setColour( 0.0,  1.0,  0.1);
  lbScore.setText("+30", 3);

  for(int i = 0; i < maxWeaponMounts; ++i) {
    WeaponMount.push_back(new BasicMount);
    WeaponMount[i]->setup(REDPLASMA);
    WeaponMount[i]->setOffset(0, 20);
  }
}

void CorruptedStarShip::update(float Px, float Py) {
  if(visible) {
    y-=speed;
    x = amp * sin(((2*M_PI)/800)*(y)) + startX;
  }

  if(y <= -height)
    setVisible(false);

  for(int i = 0; i < maxWeaponMounts; ++i) {
    if(!visible)
      WeaponMount[i]->setVisible(false);
    WeaponMount[i]->update(x, y, 0, -1, 180);
  }
}

void CorruptedStarShip::reset() {

}

void CorruptedStarShip::draw() {
  for(int i = 0; i < maxWeaponMounts; ++i)
    WeaponMount[i]->draw(); 

  if(visible) {
    glEnable(GL_TEXTURE_2D);
    if(health > maxHealth/4.0 *3) {
      glBindTexture(GL_TEXTURE_2D, getCorruptedStarShipTexture(0));
    } else if(health > maxHealth/2) {
      glBindTexture(GL_TEXTURE_2D, getCorruptedStarShipTexture(1));
    } else if(health > maxHealth/4) {
      glBindTexture(GL_TEXTURE_2D, getCorruptedStarShipTexture(2));
    } else {
      glBindTexture(GL_TEXTURE_2D, getCorruptedStarShipTexture(3));
    }

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
    glColor3f(1.0, 1.0, 1.0);
  } else {
    lbScore.setX(x);
    lbScore.setY(y);
    lbScore.draw(); 
  }
}

void CorruptedStarShip::setX(float x) {
  this->x = x;
  startX = x;
  if(x < width*5) {
    amp = (x-width)/2;//startX-width/2;
  } else if(SPACE_X_RESOLUTION - x < width*5) {
    amp = (SPACE_X_RESOLUTION - x - width)/2;
  } else {
    amp = width/2*5;
  }
}

void CorruptedStarShip::setY(float y) {
  this->y = y;
}
