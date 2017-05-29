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
  std::string str = "BasicMountBright";
  if(currentTexture == 1) {
    //glBindTexture(GL_TEXTURE_2D, getBasicMountBrightTexture());
    str = "BasicMount";
  } 
    //glBindTexture(GL_TEXTURE_2D, getBasicMountTexture());
  return str;
}

void BasicMount::defaults() {
  health = 10;
}

