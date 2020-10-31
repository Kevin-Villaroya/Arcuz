#include "View.h"

View::View(sf::RenderWindow &window, int height, int width, bool fullscreen): window(window){
  this->height = height;
  this->width = width;
  this->fullscreen = fullscreen;
}
