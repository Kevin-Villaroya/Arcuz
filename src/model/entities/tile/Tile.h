#ifndef __TILE_H__
#define __TILE_H__

#include "../EntityDrawable.h"
#include "../../../tool/TextureTool.h"
#include "poseable/AbstractPoseable.h"

enum TypeTile{
  GRASS,
  GROUND
};

class Tile : public EntityDrawable{
private:
  TypeTile type;

  AbstractPoseable* poseable;
  bool originOfPoseable; //if it's origin, we have to draw it (needed for big structures)

public:
  Tile(TypeTile type);
  TypeTile getType() const;
  void setType(TypeTile type);

  void setSpriteByType(TypeTile type);

  void setPoseable(AbstractPoseable* poseable, bool isOrigin);
  void removePoseable();

  bool isTraversable();

  AbstractPoseable* getPoseable();
  bool isOriginPoseable();

  bool update() override;

  ~Tile();
};

#endif
