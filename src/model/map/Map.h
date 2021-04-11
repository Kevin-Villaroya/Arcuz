#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include "../entities/tile/Tile.h"

class Map{
private:
  std::vector<std::vector<Tile>> tiles;
  unsigned int width;
  unsigned int lenght;

  bool outOfBounds(unsigned int x, unsigned int y);

  sf::Vector2u posSpawn;

public:
  Map();
  Map(int lenght, int width);

  int getLenght();
  int getWidth();

  sf::Vector2u getSizeTile();
  Tile& getTile(int x, int y);
  void setTile(Tile newTile, int x ,int y);

  void setSpawnPlayers();
  sf::Vector2u getPosSpawnPlayers();

  void resizeMap(unsigned int lenght, unsigned int width);

  void putIn(sf::Packet& packet) const;
  void putOut(sf::Packet& packet);
};

#endif
