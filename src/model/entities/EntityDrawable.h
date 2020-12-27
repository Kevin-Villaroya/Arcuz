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

class EntityDrawable : public sf::Sprite{
protected:
  Direction direction;
  std::string name;

  bool isSpriteFixe;
public:
  EntityDrawable();
  EntityDrawable(bool isSpriteFixe);

  unsigned int getPosX() const;
  unsigned int getPosY() const;

  unsigned int getHeight() const;
  unsigned int getWidth() const;

  bool getIsSpriteFixe() const;
  Direction getDirection() const;
  const std::string& getName() const;

  TextureTool getTextureTool() const;

  virtual void watchDirection();
  void setOriginCenter();

  void setTexture(const sf::Texture &texture);
  virtual void update();
};

sf::Packet& operator <<(sf::Packet& packet, const EntityDrawable& entity);
sf::Packet& operator >>(sf::Packet& packet, EntityDrawable& entity);

#endif
