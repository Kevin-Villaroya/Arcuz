#ifndef __TILE_H__
#define __TILE_H__

#include "../EntityDrawable.h"
#include "../../../tool/TextureTool.h"

enum TypeTile{
  GRASS,
  GROUND
};

class Tile : public EntityDrawable{
private:
  bool block;
  TypeTile type;

public:
  Tile(TypeTile type, bool block);
  TypeTile getType() const;
  void setType(TypeTile type);

  void setSpriteByType(TypeTile type);

  void update() override;
};

#endif
