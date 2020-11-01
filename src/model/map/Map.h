#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include "../entities/tile/Tile.h"

class Map{
private:
  std::vector<std::vector<Tile>> tiles;
  int width;
  int lenght;

  bool outOfBounds(int x, int y);

public:
  Map();
  Map(int lenght, int width);

  int getLenght();
  int getWidth();
  Tile getTile(int x, int y);
  void setTile(Tile newTile, int x ,int y);
};

#endif
