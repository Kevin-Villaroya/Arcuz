#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <SFML/Graphics/Sprite.hpp>
#include <string>

class SpriteTool : public sf::Sprite{
private:

public:
  SpriteTool(std::string locationFolder);
};


#endif
