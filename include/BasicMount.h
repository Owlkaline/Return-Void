#ifndef BASICMOUNT
#define BASICMOUNT

#include "./Mount.h"


class BasicMount: public Mount {
  public:
    BasicMount();
    void update(float x, float y, float directionX, float directionY, float angle);

    void setup(float offsetX, float offsetY);
    void reset();

  protected:
};

#endif
