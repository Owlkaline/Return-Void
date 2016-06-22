#include "../../include/Enemies/BasicEnemy.h"

void BasicEnemy::setup(float drop) {
  speed = 5;
  width = 75;
  height = 75;
  health = 10;
  tick = 0;
  transparent = 1.0;
  visible = true;
  maxWeaponMounts = 1;
  x = -SPACE_X_RESOLUTION;
  y = -SPACE_X_RESOLUTION;

  wasKilled = false;
  
  this->drop = drop;

  score = 10;
  lbScore.setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 0.2, true);
  lbScore.setColour( 1.0,  0.1,  0.1);
  lbScore.setText("+10", 3);

  for(int i = 0; i < maxWeaponMounts; ++i) {
    WeaponMount.push_back(new BasicMount);
    WeaponMount[i]->setup();
    WeaponMount[i]->setOffset(0, 20);
  }
}

void BasicEnemy::update(float Px, float Py) {
  if(tookDamage)
    tick--;

  if(visible)
    y-=speed;

  if(y <= -height)
    setVisible(false);

  for(int i = 0; i < maxWeaponMounts; ++i) {
    if(!visible)
      WeaponMount[i]->setVisible(false);
    WeaponMount[i]->update(x, y, 0, -1, 180);
  }
}

void BasicEnemy::reset() {

}

void BasicEnemy::draw() {
  for(int i = 0; i < maxWeaponMounts; ++i)
    WeaponMount[i]->draw();

  if(visible) {
    if(tookDamage) {
      if(tick <= 0)
        tookDamage = false;
      glColor3f(1.0, 0.0, 0.0);
    }
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, getBasicEnemyTexture());

    glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(x-width/2, y+height/2, 0.0);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(x+width/2, y+height/2, 0.0);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(x+width/2, y-height/2, 0.0);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(x-width/2, y-height/2, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0,1.0,1.0);
  } else {
    lbScore.setX(x);
    lbScore.setY(y);
    lbScore.draw();

  }
}
