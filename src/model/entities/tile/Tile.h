#ifndef __TILE_H__
#define __TILE_H__

#include "../EntityDrawable.h"
#include "../../../tool/TextureTool.h"

enum TypeTile{
  GRASS,
  GROUND,
  GROUND_GRASS
};

class Tile : public EntityDrawable{
public:
  static const TextureTool* GRASS_TEXTURE;
  static const TextureTool* GROUND_TEXTURE;
  static const TextureTool* GROUND_GRASS_TEXTURE;

private:
  bool block;
  TypeTile type;

  void setSpriteByType(TypeTile type);

public:
  Tile(TypeTile type, bool block);
  TypeTile getType() const;
  void setType(TypeTile type);
  unsigned int getLenght() const;
  unsigned int getWidth() const;
};

#endif
