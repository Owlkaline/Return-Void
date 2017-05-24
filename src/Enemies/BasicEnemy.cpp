#include "../../include/Enemies/BasicEnemy.h"

BasicEnemy::BasicEnemy() {
  this->visible = false;
  this->width = 75;
  this->height = 75;
  this->speed = 5;
  this->width = 75;
  this->height = 75;
  this->health = 10;

  this->angle = 0;
  this->isBoss = false;

  this->transparent = 1.0;

  this->maxWeaponMounts = 1;

  this->score = 10;
  
  this->WeaponMount.push_back(new MountType1(0, 20));
}

BasicEnemy::~BasicEnemy() {
  clean();
}

void BasicEnemy::update(float Px, float Py, float deltaTime) {
  move(deltaTime);

  if(tookDamage)
    tick--;
  for(int i = 0; i < maxWeaponMounts; ++i) {
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

void BasicEnemy::reset() {

}

std::string BasicEnemy::getTexture() {
    //if(tookDamage)
      //glColor3f(1.0, 0.0, 0.0);
    //glBindTexture(GL_TEXTURE_2D, getBasicEnemyTexture());
  return "BasicEnemy";
}
