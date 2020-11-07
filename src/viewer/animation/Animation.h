#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <vector>
#include <string>
#include "../../tool/TextureTool.h"

class Animation{

private:
  std::vector<TextureTool> animation;
  const unsigned int delay;

  unsigned int currentFrame;
  unsigned int currentDelay;

  void increaseFrame();
public:
  Animation();
  Animation(const std::vector<TextureTool*> &textures);
  Animation(const std::vector<TextureTool*> &textures, unsigned int delay);
  void addTexture(const TextureTool &texture);
  sf::Texture& getTextureDisplay();
  void reset();
  bool isLastFrame();
};

#endif
