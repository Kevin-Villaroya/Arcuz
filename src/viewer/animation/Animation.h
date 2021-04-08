#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <vector>
#include <string>
#include "../../tool/TextureTool.h"

class Animation{

private:
  std::vector<TextureTool*> animation;
  unsigned int delay;

  unsigned int currentFrame;
  unsigned int currentDelay;

  std::string name;

  void increaseFrame();
public:
  Animation();
  Animation(const std::vector<TextureTool*> &textures);
  Animation(const std::vector<TextureTool*> &textures, unsigned int delay, std::string name);
  void addTexture(TextureTool* texture);

  const sf::Texture* getTextureDisplay();
  unsigned int getCurrentFrame();

  unsigned int getDelay();
  void setDelay(unsigned int delay);

  const std::string& getName();
  void setName(std::string name);

  void reset();
  bool isLastFrame();
};

#endif
