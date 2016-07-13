#include "../../include/Enemies/HypnoEnemy.h"

HypnoEnemy::~HypnoEnemy() {
  clean();
}

void HypnoEnemy::setup(float drop) {
  speed = 5;
  width = 75;
  height = 75;
  health = 7;
  angle = 0;
  moveType = SEMICIRCLE;
  tookDamage = false;
  maxHealth = health;
  tick = 0;
  visible = true;
  maxWeaponMounts = 2;
  x = -SPACE_X_RESOLUTION;
  y = -SPACE_Y_RESOLUTION;
  hasFinished = false;

  wasKilled = false;
  
  this->drop = drop; 
  
  movementAngle = 180;

  score = 70;
  lbScore.setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 0.2, true);
  lbScore.setColour( 0.0,  1.0,  0.1);
  lbScore.setText("+70", 3);

  for(int i = 0; i < maxWeaponMounts; ++i) {
    WeaponMount.push_back(new HypnoMount);
    WeaponMount[i]->setup(i);
    
  }
  WeaponMount[0]->setOffset(15, 30);
  WeaponMount[1]->setOffset(-15, 30);
}

void HypnoEnemy::update(float Px, float Py) {    
  if(visible) {
     if(y < SPACE_Y_RESOLUTION+height) {
      if(!rightSide) {
        movementAngle+=speed/10;
        x = SPACE_X_RESOLUTION/2 + cos(movementAngle/ 180.0f * (float)M_PI) * startX;
        y = SPACE_Y_RESOLUTION + sin(movementAngle/ 180.0f * (float)M_PI) * SPACE_Y_RESOLUTION/2+height;
      } else {
        movementAngle-=speed/10;
        x = SPACE_X_RESOLUTION/2 + cos(movementAngle/ 180.0f * (float)M_PI) * -startX;
        y = SPACE_Y_RESOLUTION + sin(movementAngle/ 180.0f * (float)M_PI) * -SPACE_Y_RESOLUTION/2+height;
      }
      hasFinished = true;
     } else {
       if(!hasFinished) {
         y-=speed;
       } else {
         visible = false;
       }
     }
  }
    
  float diffx = Px - x;
  float diffy = Py - y;
 
  if (diffx > 0.0 && diffy > 0.0) {//Quadrant 1
    angle = (float)atan(diffy/diffx) *180.0f / (float)M_PI ;
    angle = angle - 90.0f;
  }else if(diffx < 0 && diffy > 0) {//Quadrant 2
    angle = (float)atan(diffy/diffx) *180.0f / (float)M_PI ;
    angle = angle + 90.0f;
  } else     if(diffx < 0 && diffy < 0) {//Quadrant 3
     angle = (float)atan(diffy/diffx) *180.0f / (float)M_PI ;
     angle = angle+90.0f;
  } else     if(diffx > 0 && diffy < 0) {//Quadrant 4
     angle = (float)atan(diffy/diffx) * 180.0f / (float)M_PI ;
     angle = angle - 90.0f;
  }

  for(int i = 0; i < maxWeaponMounts; ++i) {
    if(!visible)
      WeaponMount[i]->setVisible(false);
    WeaponMount[i]->update(x, y, 0, -1, angle, Px, Py);
  }
}

void HypnoEnemy::reset() {

}

void HypnoEnemy::setTexture() {
    glBindTexture(GL_TEXTURE_2D, getHypnoEnemyTexture());
}

void HypnoEnemy::setX(float x) {
  this->x = 0;
  if(x < width*5) {
    amp = (x-width)/2;//startX-width/2;
  } else if(SPACE_X_RESOLUTION - x < width*5) {
    amp = (SPACE_X_RESOLUTION - x - width)/2;
  } else {
    amp = width/2*5;
  }
  if(x > SPACE_X_RESOLUTION/2) {
    startX = x - amp;
    rightSide = false;
  } else {
    startX = x + amp;
    rightSide = true;
    angle = 0;
  }
}

void HypnoEnemy::setY(float y) {
  this->y = y;
  startY = y;
}
