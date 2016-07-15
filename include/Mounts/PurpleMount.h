#ifndef PURPLEMOUNT_H
#define PURPLEMOUNT_H

#include "./Mount.h"

class PurpleMount: public Mount {
  public:
    PurpleMount();
    ~PurpleMount();
    
    void setTexture();
    void reset();
    void defaults();
    void update(float x, float y, float directionX, float directionY, float angle, bool isShooting);
    void update(float x, float y, float directionX, float directionY, float angle, float Px, float Py);

  protected:   
};

#endif
