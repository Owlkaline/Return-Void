#include "../../include/Enemies/HypnoEnemy.h"

void HypnoEnemy::setup(float drop) {
  speed = 5;
  width = 75;
  height = 75;
  health = 7;
  maxHealth = health;
  tick = 0;
  visible = true;
  maxWeaponMounts = 2;
  x = -SPACE_X_RESOLUTION;
  y = -SPACE_X_RESOLUTION;

  wasKilled = false;
  
  this->drop = drop; 
  
  movementAngle = 180;

  score = 70;
  lbScore.setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 0.2, true);
  lbScore.setColour( 0.0,  1.0,  0.1);
  lbScore.setText("+70", 3);

  for(int i = 0; i < maxWeaponMounts; ++i) {
    WeaponMount.push_back(new HypnoMount);
    WeaponMount[i]->setup(i);
    
  }
  WeaponMount[0]->setOffset(15, 30);
  WeaponMount[1]->setOffset(-15, 30);
}

void HypnoEnemy::update(float Px, float Py) {    
  if(visible) {
     if(y < SPACE_Y_RESOLUTION+height) {
      if(!rightSide) {
        movementAngle+=speed/10;
        x = SPACE_X_RESOLUTION/2 + cos(movementAngle/ 180.0f * (float)M_PI) * startX;
        y = SPACE_Y_RESOLUTION + sin(movementAngle/ 180.0f * (float)M_PI) * SPACE_Y_RESOLUTION/2+height;
      } else {
        movementAngle-=speed/10;
        x = SPACE_X_RESOLUTION/2 + cos(movementAngle/ 180.0f * (float)M_PI) * -startX;
        y = SPACE_Y_RESOLUTION + sin(movementAngle/ 180.0f * (float)M_PI) * -SPACE_Y_RESOLUTION/2+height;
      }
      hasFinished = true;
     } else {
       if(!hasFinished) {
         y-=speed;
       } else {
         visible = false;
       }
     }
  }
    
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

  for(int i = 0; i < maxWeaponMounts; ++i) {
    if(!visible)
      WeaponMount[i]->setVisible(false);
    WeaponMount[i]->update(x, y, 0, -1, angle, Px, Py);
  }
}

void HypnoEnemy::reset() {

}

void HypnoEnemy::draw() {
  if(visible) {
    if(tookDamage) {
      if(tick <= 0)
        tookDamage = false;

    }
    glEnable(GL_TEXTURE_2D);
    //if(health > maxHealth/4.0 *3) {
      glBindTexture(GL_TEXTURE_2D, getHypnoEnemyTexture());
   // } else if(health > maxHealth/2) {
   //   glBindTexture(GL_TEXTURE_2D, getHypnoEnemyTexture(1));
   // } else if(health > maxHealth/4) {
   //   glBindTexture(GL_TEXTURE_2D, getHypnoEnemyTexture(2));
  //  } else {
   //   glBindTexture(GL_TEXTURE_2D, getHypnoEnemyTexture(3));
  //  }
    glPushMatrix();
    glTranslatef(x, y, 0); // M1 - 2nd translation
    glRotatef(angle, 0.0f, 0.0f, 1.0f);  
    glTranslatef(-x, -y, 0); // M1 - 2nd translation
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
    glPopMatrix();
    glColor3f(1.0, 1.0, 1.0);
  } else {
    lbScore.setX(x);
    lbScore.setY(y);
    lbScore.draw(); 
  }
  for(int i = 0; i < maxWeaponMounts; ++i)
    WeaponMount[i]->draw(); 
}

void HypnoEnemy::setX(float x) {
  //this->x = x;  
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
    rightSide = false;
  } else {
    startX = x + amp;
    rightSide = true;
    angle = 0;
  }
}

void HypnoEnemy::setY(float y) {
  this->y = y;
  startY = y;
}
