#include "../../include/Mounts/DotMount.h"

DotMount::DotMount() {
  visible = false;
  width = 75/3.73;
  height = 75/3.73;
}

DotMount::~DotMount() {
  clean();
}

std::string DotMount::getTexture() {
  //glBindTexture(GL_TEXTURE_2D, getDotMountTexture(isLeft));
  return "DotMount";
}

void DotMount::defaults() {
  width = 75/3.73;
  height = 75/3.73;
  health = 20;
}


