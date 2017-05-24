#ifndef PURPLEMOUNT_H
#define PURPLEMOUNT_H

#include "./Mount.h"

class PurpleMount: public Mount {
  public:
    PurpleMount();
    ~PurpleMount();
    
    std::string getTexture();
    void defaults();
  protected:   
};

#endif
