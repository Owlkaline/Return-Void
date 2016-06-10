#include "../include/BasicEnemy.h"

void BasicEnemy::setup() {
  width = 75;
  height = 75;
  maxWeaponMounts = 1;
  visible = true;
  x = -SPACE_X_RESOLUTION;
  y = -SPACE_X_RESOLUTION;
  Texture = txt::LoadTexture("Textures/Game/Enemies/BasicEnemy.png");
  for(int i = 0; i < maxWeaponMounts; ++i) {
    WeaponMount.push_back(new BasicMount);
    WeaponMount[i]->setup();
    WeaponMount[i]->setOffset(0, 20);
  }
}
 
void BasicEnemy::update() {
  y-=5;
  if(y <= -height)
    visible = false;
  for(int i = 0; i < maxWeaponMounts; ++i) 
    WeaponMount[i]->update(x, y, 0, -1, 180);
  
  
  
}
 
void BasicEnemy::reset() {

}

void BasicEnemy::draw() {
  for(int i = 0; i < maxWeaponMounts; ++i) 
    WeaponMount[i]->draw();
    
  glEnable(GL_TEXTURE_2D); 
  glBindTexture(GL_TEXTURE_2D, Texture);
  
 // glColor3f(0.0, 0.0, 1.0);
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
}
