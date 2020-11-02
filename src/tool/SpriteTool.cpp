#include "SpriteTool.h"
#include "TextureTool.h"

SpriteTool::SpriteTool(std::string locationFolder){
  this->setTexture(TextureTool(locationFolder));
}
