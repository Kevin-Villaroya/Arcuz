#include "SpriteTool.h"
#include "TextureTool.h"


SpriteTool::SpriteTool() : sf::Sprite(){}

SpriteTool::SpriteTool(std::string locationFolder) : sf::Sprite(){
  this->setTexture(TextureTool(locationFolder));
}
