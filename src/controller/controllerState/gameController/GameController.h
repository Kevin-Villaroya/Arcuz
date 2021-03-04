#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "../../../model/modelGame/Model.h"
#include "../../../tool/SpriteTool.h"
#include "../../Controller.h"

class GameController : public Controller{
protected:
  unsigned int nextIdScreen = 0;
  sf::Image* icon;

  Model* model;
  View* view;

public:
  static const unsigned int id = 1;
  
  GameController(sf::RenderWindow* window);
  GameController(int width, int height);
  virtual void checkEvents();

  virtual void start() override;
  void run();
  void closeController() override;

  unsigned int getId();
  virtual unsigned int nextId() override;

  virtual ~GameController();
};
#endif
