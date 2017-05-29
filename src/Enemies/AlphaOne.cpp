#include "../../include/Enemies/AlphaOne.h"

AlphaOne::AlphaOne() {
  this->visible = false;
  this->width = 256;
  this->height = 30;
  this->speed = 5;
  this->width = 256;
  this->height = 128;
  this->health = 120;//30;

  this->angle = 0;
  this->isBoss = true;

  this->transparent = 1.0;

  this->maxWeaponMounts = 2;

  this->score = 500;

  this->WeaponMount.push_back(new AlphaOneMount);
  this->WeaponMount[0]->setIsBoss();
  this->WeaponMount[0]->setup(ALPHAONEPLASMA);
  this->WeaponMount[0]->setOffset(128, 0);

  this->WeaponMount.push_back(new AlphaOneMount);
  this->WeaponMount[1]->setIsBoss();
  this->WeaponMount[1]->setup(ALPHAONEPLASMA);
  this->WeaponMount[1]->setOffset(-128, 0);  
  this->WeaponMount[1]->isLeftMount();
}

AlphaOne::~AlphaOne() {
  clean();
}

void AlphaOne::defaults() {
  
}

void AlphaOne::update(float Px, float Py, float deltaTime) {
  move(deltaTime);

  if(tookDamage)
    tick--;
  for(unsigned int i = 0; i < WeaponMount.size(); ++i) {
    if(!visible)
      WeaponMount[i]->setVisible(false);

    float rad = (movementAngle+90) * M_PI/180.0;
    float dirx = cos(-rad) * width;
    float diry = sin(-rad) * height;
    float distance = pow(pow(diry,2.0f) + pow(dirx,2.0f), 0.5f);
    dirx = dirx/distance;
    diry = diry/distance;
    WeaponMount[i]->update(x, y, deltaTime, dirx, diry, angle+180, true);
  }
}

void AlphaOne::reset() {

}

std::string AlphaOne::getTexture() {
    //if(tookDamage)
    //  glColor3f(1.0, 0.0, 0.0);
    //glBindTexture(GL_TEXTURE_2D, getAlphaOneTexture());
  std::string str = "AlphaOne";
  return str;
}
