#include "../../include/Mounts/BasicMount.h"

BasicMount::BasicMount() {
  this->visible = false;
  this->width = 8;
  this->height = 64;
}

BasicMount::~BasicMount() {
  clean();
}


std::string BasicMount::getTexture() {
  if(currentTexture == 1) {
    //glBindTexture(GL_TEXTURE_2D, getBasicMountBrightTexture());
    return "BasicMount";
  } 
    //glBindTexture(GL_TEXTURE_2D, getBasicMountTexture());
  return "BasicMountBright";
}

void BasicMount::defaults() {
  health = 10;
}

