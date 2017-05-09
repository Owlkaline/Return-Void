#include "../../include/Misc/Effects.h"

Effects *Effects::m_instance = 0;

Effects::Effects() {

}

Effects::~Effects() {

}


Effects *Effects::init() {
  if(!Effects::m_instance) {
    Effects::m_instance = new Effects;
  } else {
    printf(("WARNING: Effects::init() has already been called.\n"));
    exit(-1);
  }
  return Effects::m_instance;
}

Effects *Effects::instance() {
  if(!Effects::m_instance) {
    return Effects::init();
  } else
    return Effects::m_instance;
}

void Effects::destroy() {
  delete Effects::m_instance;
  Effects::m_instance = 0;
}
    
void Effects::addSmallExplosion(float x, float y, float dirX, float dirY) {
  smallExplo.push_back(new SmallExplosion);
  int size = smallExplo.size()-1;
  smallExplo[size]->setup(x, y, dirX, dirY);
}

void Effects::draw() {
  for(unsigned int i = 0; i < smallExplo.size(); ++i) 
    smallExplo[i]->draw();
}

void Effects::update(float deltaTime) {
  for(unsigned int i = 0; i < smallExplo.size(); ++i) { 
    smallExplo[i]->update(deltaTime);
    if(smallExplo[i]->hasExpired()) {
      smallExplo.erase(smallExplo.begin() + i);  
    }
  }
}
