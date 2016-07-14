#include "../../include/Enemies/BasicEnemy.h"

BasicEnemy::BasicEnemy() {
  width = 75;
  height = 75;
}

BasicEnemy::~BasicEnemy() {
  clean();
}

void BasicEnemy::defaults() {
  printf("Basic Enemy setup\n");
  speed = 5;
  width = 75;
  height = 75;
  health = 10;

  angle = 0;

  transparent = 1.0;

  maxWeaponMounts = 1;

  score = 10;
  lbScore.setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 0.2, true);
  lbScore.setColour( 1.0,  0.1,  0.1);
  lbScore.setText("+10", 3);

  for(int i = 0; i < maxWeaponMounts; ++i) {
    WeaponMount.push_back(new BasicMount);
    WeaponMount[i]->setup(BLUEPLASMA);
    WeaponMount[i]->setOffset(0, 20);
  }
}

void BasicEnemy::update(float Px, float Py) {
  move();

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
    WeaponMount[i]->update(x, y, dirx, diry, angle+180, true);
  }
}

void BasicEnemy::reset() {

}

void BasicEnemy::setTexture() {
    if(tookDamage)
      glColor3f(1.0, 0.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, getBasicEnemyTexture());
}
