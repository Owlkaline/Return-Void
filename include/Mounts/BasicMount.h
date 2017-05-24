#ifndef BASICMOUNT_H
#define BASICMOUNT_H

#include "./Mount.h"

class BasicMount: public Mount {
  public:
    BasicMount();
    ~BasicMount();
    
    std::string getTexture();
    void defaults();
  protected:   
   
};

#endif
