#include "../../include/Enemies/AlphaOne.h"

AlphaOne::AlphaOne() {

}

AlphaOne::~AlphaOne() {
  clean();
}

void AlphaOne::defaults() {
  speed = 5;
  width = 256;
  height = 128;
  health = 30;

  angle = 0;
  isBoss = true;

  transparent = 1.0;

  maxWeaponMounts = 2;

  score = 500;
  lbScore.setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 0.4, true);
  lbScore.setColour( 1.0,  0.1,  0.1);
  lbScore.setText("+500", 3);

  for(int i = 0; i < maxWeaponMounts; ++i) {
    WeaponMount.push_back(new BasicMount);
    WeaponMount[i]->setup(BLUEPLASMA);
    WeaponMount[i]->setOffset(0, 20);
  }
}

void AlphaOne::update(float Px, float Py) {
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

void AlphaOne::reset() {

}

void AlphaOne::setTexture() {
    if(tookDamage)
      glColor3f(1.0, 0.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, getAlphaOneTexture());
}
