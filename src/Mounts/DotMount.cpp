#include "../../include/Mounts/DotMount.h"

DotMount::DotMount() {
  visible = false;
  width = 75/3.73;
  height = 75/3.73;
}

DotMount::~DotMount() {
  clean();
}

void DotMount::setTexture() {
  //glBindTexture(GL_TEXTURE_2D, getDotMountTexture(isLeft));
}

void DotMount::reset() {

}

void DotMount::defaults() {
  width = 75/3.73;
  height = 75/3.73;
  health = 20;
}


