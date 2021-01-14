#ifndef __ENTITY_DRAWABLE_H__
#define __ENTITY_DRAWABLE_H__

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Network/Packet.hpp>
#include "../../tool/TextureTool.h"

enum Direction{
  left,
  right,
  up,
  down
};

enum TypeEntity{
  character,
  tile
};

class EntityDrawable : public sf::Sprite{
protected:
  Direction direction;
  TypeEntity typeEntity;
  std::string name;
  int uid;

  bool isSpriteFixe;
public:
  EntityDrawable();
  EntityDrawable(bool isSpriteFixe);

  unsigned int getPosX() const;
  unsigned int getPosY() const;

  unsigned int getHeight() const;
  unsigned int getWidth() const;

  int getUid();
  void setUid(unsigned int uid);

  bool getIsSpriteFixe() const;
  Direction getDirection() const;
  const std::string& getName() const;

  TextureTool getTextureTool() const;

  virtual void watchDirection();
  void setOriginCenter();

  void setTexture(const sf::Texture &texture);
  virtual void update();

  virtual void putIn(sf::Packet& packet) const;
  virtual void putOut(sf::Packet& packet);
};

#endif
