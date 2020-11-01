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

public:
  Controller(int width, int height);
  void checkEvents();

  void start();
  void closeGame();

  ~Controller();
};
#endif
