#ifndef __VIEW_H__
#define __VIEW_H__

#include <SFML/Graphics.hpp>
#include <vector>
#include "../model/entities/EntityDrawable.h"

class View{
private:
  int height;
  int width;
  sf::RenderWindow& window;
public:
  View(sf::RenderWindow &window, int height, int width);
  void render(const std::vector<EntityDrawable> &entities);
};

#endif
