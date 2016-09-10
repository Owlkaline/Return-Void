#ifndef EFFECTS_H
#define EFFECTS_H

#include "../defines.h"

#include "./SmallExplosion.h"

#include <vector>

class Effects {
  public:
    ~Effects();
    
    static Effects *init();
    static Effects *instance();
    static void destroy();
    
    void addSmallExplosion(float x, float y, float dirX, float dirY);
    void draw();
    void update(float deltaTime);
    
  protected:
    std::vector<SmallExplosion*> smallExplo;
    GLuint texture;
    
    Effects();
    static Effects *m_instance;    
};

#endif
