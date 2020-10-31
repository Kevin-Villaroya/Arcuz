#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "../model/Model.h"
#include <SFML/Graphics.hpp>

class Controller{
private:
  Model* model;
  View* view;
  sf::RenderWindow window; //WINDOWS IN SFML ARE DISPLAYERS AND LISTENERS
  bool running;

  void makeWindow(int width, int height, bool fullscreen);

public:
  Controller(int width, int height, bool fullscreen);
  void start();
};

#endif
