#ifndef DOTMOUNT_H
#define DOTMOUNT_H

#include "./Mount.h"

class DotMount: public Mount {
  public:
    DotMount();
    ~DotMount();
      
    void reset();
    void defaults();
    void setTexture();
    void draw() {      
      for(unsigned int i = 0; i < bullets.size(); ++i)
        bullets[i]->draw();
    }
    
  protected:
};

#endif
