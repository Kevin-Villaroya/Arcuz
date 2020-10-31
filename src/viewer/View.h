#ifndef __VIEW_H__
#define __VIEW_H__

#include <SFML/Graphics.hpp>

class View{
private:
  int height;
  int width;
  bool fullscreen;
  sf::RenderWindow& window;
public:
  View(sf::RenderWindow &window, int height, int width, bool fullscreen);
  bool isShown();
};

#endif
