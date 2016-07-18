#include "../../include/Enemies/AlphaOne.h"

AlphaOne::AlphaOne() {
  visible = false;
  width = 256;
  height = 30;
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
 // lbScore.setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 0.4, true);
 // lbScore.setColour( 1.0,  0.1,  0.1);
 // lbScore.setText("+500", 4);

  WeaponMount.push_back(new AlphaOneMount);
  WeaponMount[0]->setIsBoss();
  WeaponMount[0]->setup(ALPHAONEPLASMA);
  WeaponMount[0]->setOffset(128, 0);

  WeaponMount.push_back(new AlphaOneMount);
  WeaponMount[1]->setIsBoss();
  WeaponMount[1]->setup(ALPHAONEPLASMA);
  WeaponMount[1]->setOffset(-128, 0);  
  WeaponMount[1]->isLeftMount();
}

void AlphaOne::update(float Px, float Py) {
  move();

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
