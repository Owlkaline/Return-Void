#ifndef AlphaOneMount_H
#define AlphaOneMount_H

#include "./Mount.h"

class AlphaOneMount: public Mount {
  public:
    AlphaOneMount();
    ~AlphaOneMount();
    
    void setTexture();
    void reset();
    void defaults();
    void update(float x, float y, float directionX, float directionY, float angle, bool isShooting);
    void update(float x, float y, float directionX, float directionY, float angle, float Px, float Py);

  protected:   
   
};

#endif
