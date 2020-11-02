#ifndef __SPRITE_TOOL_H__
#define __SPRITE_TOOL_H__

#include <SFML/Graphics/Sprite.hpp>
#include <string>

class SpriteTool : public sf::Sprite{
private:

public:
  SpriteTool();
  SpriteTool(std::string locationFolder);
};


#endif
