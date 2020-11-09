#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "../model/Model.h"
#include <SFML/Graphics.hpp>

class Controller{
protected:
  Model* model;
  View* view;
  sf::RenderWindow window; //WINDOWS IN SFML ARE DISPLAYERS AND LISTENERS
  bool running;

public:
  Controller(int width, int height);
  virtual void checkEvents();

  virtual void start();
  void closeGame();

  virtual ~Controller();
};
#endif
