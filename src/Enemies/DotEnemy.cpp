#include "../../include/Enemies/DotEnemy.h"

DotEnemy::DotEnemy() {
  visible = false;
  width = 20;
  height = 20;
}

DotEnemy::~DotEnemy() {
  clean();
}

void DotEnemy::defaults() {
  speed = 10;
  width = 30;
  height = 30;
  health = 3;
  angle = 0; 
 
  maxWeaponMounts = 1;
  isBoss = false;
  
  movementAngle = 0;

  score = 10;

  for(int i = 0; i < maxWeaponMounts; ++i) {
    WeaponMount.push_back(new DotMount);
    WeaponMount[i]->setup(DOTBULLET);
  }
  
  WeaponMount[0]->isLeftMount();
  
  WeaponMount[0]->setOffset(0, 0);
  //WeaponMount[1]->setOffset(-15, 30);
}

void DotEnemy::update(float Px, float Py) {    
  move(); 
    
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

  for(unsigned int i = 0; i < WeaponMount.size(); ++i) {
    if(!visible)
      WeaponMount[i]->setVisible(false);
    WeaponMount[i]->update(x, y, 0, -1, angle, Px, Py);
  }
}
 
void DotEnemy::reset() {

}

void DotEnemy::setTexture() {
    glBindTexture(GL_TEXTURE_2D, getDotEnemyTexture());
}

void DotEnemy::setX(float x) {
  this->x = 0;
}

void DotEnemy::setY(float y) {
  this->y = y;
}
