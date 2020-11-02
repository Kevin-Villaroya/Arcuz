#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>

#include "../viewer/View.h"
#include "entities/EntityDrawable.h"
#include "map/Map.h"
#include "entities/character/Character.h"

class Model{
private:
  View view;
  Map map;
  Character mainCharacter;

  std::vector<EntityDrawable> entities; //all entities in the game (without character)

public:
  Model(View &view);
  void update();
  void render();
};

#endif
