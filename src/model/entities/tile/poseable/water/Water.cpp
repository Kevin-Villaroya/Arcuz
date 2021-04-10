#include "Water.h"
#include "../../../../../viewer/texture/StructureTexture.h"
#include <iostream>

Water::Water() : AbstractPoseable("water", false, false){
  this->addAnimation(Animation(StructureTexture::getTexturesOf("water")), "idle");
  this->setDelayOfAnimation(9);
  this->playAnimation("idle");
}