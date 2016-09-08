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
  
  for(int i = 0; i < maxWeaponMounts; ++i) {
    this->WeaponMount.push_back(new BasicMount);
    this->WeaponMount[i]->setup(BLUEPLASMA);
    this->WeaponMount[i]->setOffset(0, 20);
  }
}

BasicEnemy::~BasicEnemy() {
  clean();
}

void BasicEnemy::defaults() {
 
 // lbScore.setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 0.2, true);
//  lbScore.setColour( 1.0,  0.1,  0.1);
//  lbScore.setText("+10", 3);


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

void BasicEnemy::setTexture() {
    if(tookDamage)
      glColor3f(1.0, 0.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, getBasicEnemyTexture());
}
