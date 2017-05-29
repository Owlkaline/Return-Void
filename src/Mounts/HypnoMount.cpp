#include "../../include/Mounts/HypnoMount.h"

HypnoMount::HypnoMount() {
  visible = false;
  width = 75/3.73;
  height = 75/3.73;
}

HypnoMount::~HypnoMount() {
  clean();
}

std::string HypnoMount::getTexture() {
  //glBindTexture(GL_TEXTURE_2D, getHypnoMountTexture(isLeft));
  std::string str = "HypnoMountRight";
  if(isLeft == 0)
    str = "HypnoMountLeft";
  return str;
}

void HypnoMount::defaults() {
  width = 75/3.73;
  height = 75/3.73;
  health = 20;
}


