#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <vector>
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include "../../tool/TextureTool.h"

class Animation{

private:
  std::vector<sf::Sprite> animation;
  const unsigned int delay;

  unsigned int currentFrame;
  unsigned int currentDelay;

  void increaseFrame();
public:
  Animation();
  Animation(std::vector<sf::Sprite> &animation);
  Animation(std::vector<TextureTool> &textures);
  Animation(std::vector<sf::Sprite> &animation, unsigned int delay);
  Animation(std::vector<TextureTool> &textures, unsigned int delay);
  void addSprite(sf::Sprite sprite);
  sf::Sprite play();
  void reset();
};

#endif
