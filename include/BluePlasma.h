#ifndef BLUE_PLASMA
#define BLUE_PLASMA

#include "./Weapon.h"
#include "./defines.h"

class BluePlasma: public Weapon {
  public:
    BluePlasma();
    void update();
    void draw();
    void setup(float x, float y, float dirX, float dirY, float angle);
    void reset();
    void clean();
  protected:
  
};

#endif
