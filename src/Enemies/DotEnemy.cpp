#include "../../include/Enemies/DotEnemy.h"

DotEnemy::DotEnemy() {
  this->visible = false;
  this->width = 20;
  this->height = 20;
  
  this->speed = 8;
  this->width = 30;
  this->height = 30;
  this->health = 3;
  this->angle = 0; 
 
  this->maxWeaponMounts = 1;
  this->isBoss = false;
  
  this->movementAngle = 0;

  this->score = 10;

  for(int i = 0; i < maxWeaponMounts; ++i) {
    this->WeaponMount.push_back(new DotMount);
    this->WeaponMount[i]->setup(DOTBULLET);
  }
  
  this->WeaponMount[0]->isLeftMount();
  
  this->WeaponMount[0]->setOffset(0, 0);
  this->drop = NOTHING;
}

DotEnemy::~DotEnemy() {
  clean();
}

void DotEnemy::defaults() {

  //WeaponMount[1]->setOffset(-15, 30);
}

void DotEnemy::update(float Px, float Py, float deltaTime) {    
  move(deltaTime); 
    
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
  angle*=-1;
  
  for(unsigned int i = 0; i < WeaponMount.size(); ++i) {
    if(!visible)
      WeaponMount[i]->setVisible(false);
    WeaponMount[i]->update(x, y, deltaTime, 0, -1, angle, Px, Py);
  }
}
 
void DotEnemy::reset() {

}

std::string DotEnemy::getTexture() {
//    glBindTexture(GL_TEXTURE_2D, getDotEnemyTexture());
  std::string str = "DotEnemy";
  return str;
}

void DotEnemy::setX(float x) {
  this->x = 0;
}

void DotEnemy::setY(float y) {
  this->y = y;
}
