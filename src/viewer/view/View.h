#ifndef __VIEW_H__
#define __VIEW_H__

#include <SFML/Graphics.hpp>
#include <vector>
#include "../model/entities/EntityDrawable.h"
#include "../model/entities/character/Character.h"

class View{
private:
  int height;
  int width;
  sf::RenderWindow& window;
  sf::View viewCharacter;

public:
  View(sf::RenderWindow &window, int height, int width);
  void render(const Character &character, const std::vector<EntityDrawable> &entities);
  void centerViewOn(const Character &character);
};

#endif
