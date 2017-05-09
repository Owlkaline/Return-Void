#ifndef BASICMOUNT_H
#define BASICMOUNT_H

#include "./Mount.h"

class BasicMount: public Mount {
  public:
    BasicMount();
    ~BasicMount();
    
    void setTexture();
    void defaults();
  protected:   
   
};

#endif
