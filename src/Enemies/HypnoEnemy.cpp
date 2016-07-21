#include "../../include/Enemies/HypnoEnemy.h"

HypnoEnemy::HypnoEnemy() {
  visible = false;
  width = 75;
  height = 75;
}

HypnoEnemy::~HypnoEnemy() {
  clean();
}

void HypnoEnemy::defaults() {
  speed = 5;
  width = 75;
  height = 75;
  health = 7;
  angle = 0; 
 
  maxWeaponMounts = 2;
  isBoss = false;
  
  movementAngle = 180;

  score = 50;
 // lbScore.setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 0.2, true);
 // lbScore.setColour( 0.0,  1.0,  0.1);
 // lbScore.setText("+70", 3);

  for(int i = 0; i < maxWeaponMounts; ++i) {
    WeaponMount.push_back(new HypnoMount);
    WeaponMount[i]->setup(SPIRAL);
  }
  
  WeaponMount[0]->isLeftMount();
  
  WeaponMount[0]->setOffset(15, 30);
  WeaponMount[1]->setOffset(-15, 30);
}

void HypnoEnemy::update(float Px, float Py) {    
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
    isOnRightSide = false;
  } else {
    startX = x + amp;
    isOnRightSide = true;
    angle = 0;
  }
}

void HypnoEnemy::setY(float y) {
  this->y = y;
  startY = y;
}
