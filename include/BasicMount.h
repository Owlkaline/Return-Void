#ifndef BASICMOUNT
#define BASICMOUNT

#include "./Mount.h"
#include "./BluePlasma.h"

class BasicMount: public Mount {
  public:
    BasicMount();
    void update(float x, float y, float directionX, float directionY, float angle);
    void draw();
    void setup(float offsetX, float offsetY);
    void reset();
    void clean();
    void fire(float directionX, float directionY);
  protected:
    std::vector<Weapon*> bullets;
    int tick;
};

#endif
