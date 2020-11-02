#ifndef __ANIMAION_H__
#define __ANIMAION_H__

#include <vector>
#include <string>
#include <SFML/Graphics/Sprite.hpp>

class Animation{

private:
  std::vector<sf::Sprite> animation;
  const unsigned int delay;

  unsigned int currentFrame;
  unsigned int currentDelay;

  void increaseFrame();
public:
  Animation();
  Animation(std::vector<sf::Sprite> animation);
  Animation(std::vector<sf::Sprite> animation, unsigned int delay);
  void addSprite(sf::Sprite sprite);
  sf::Sprite play();
  void reset();
};

#endif
