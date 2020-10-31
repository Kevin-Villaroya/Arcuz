#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>

#include "../viewer/View.h"
#include "entities/EntityDrawable.h"
#include "map/Map.h"

class Model{
private:
  View view;

  std::vector<EntityDrawable> entities;
  Map map;

public:
  Model(View &view);
  void update();
  void render();
};

#endif
