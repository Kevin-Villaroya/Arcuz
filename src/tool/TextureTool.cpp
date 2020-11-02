#include "TextureTool.h"

TextureTool::TextureTool() : sf::Texture() {}

TextureTool::TextureTool(std::string locationFolder) : sf::Texture(){
  this->loadFromFile(locationFolder);
}
