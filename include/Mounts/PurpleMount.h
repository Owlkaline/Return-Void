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
  protected:   
};

#endif
