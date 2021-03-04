#include "FontTool.h"

const FontTool FontTool::REGULAR_FONT = FontTool("assets/font/regular.ttf");

FontTool::FontTool() : sf::Font(){}

FontTool::FontTool(const std::string& locationFolder) : sf::Font(){
  this->loadFromFile(locationFolder);
}
