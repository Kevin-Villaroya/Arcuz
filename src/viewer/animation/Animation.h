#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <vector>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include "../../tool/TextureTool.h"

class Animation{

private:
  std::vector<sf::Texture> animation;
  const unsigned int delay;

  unsigned int currentFrame;
  unsigned int currentDelay;

  void increaseFrame();
public:
  Animation();
  Animation(const std::vector<TextureTool*> &textures);
  Animation(const std::vector<TextureTool*> &textures, unsigned int delay);
  void addTexture(const sf::Texture &texture);
  sf::Texture& getTextureDisplay();
  void reset();
  bool isLastFrame();
};

#endif
