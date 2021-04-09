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

  unsigned int oldPosX;
  unsigned int oldPosY;

  bool isSpriteFixe;

  sf::Vector2f collisionPoint;
public:
  EntityDrawable();
  EntityDrawable(bool isSpriteFixe);

  unsigned int getPosX() const;
  unsigned int getPosY() const;

  void setPosition(float x, float y);
  void setPosition(const sf::Vector2f &postion);

  void move(float x, float y);
  void move(const sf::Vector2f &offset);

  unsigned int getHeight() const;
  unsigned int getWidth() const;

  int getUid();
  void setUid(unsigned int uid);

  bool getIsSpriteFixe() const;
  Direction getDirection() const;
  const std::string& getName() const;
  void setName(const std::string& name);
  const int getIndexTypeEntity() const;

  TextureTool getTextureTool() const;

  virtual void watchDirection();
  void setOriginCenter();
  sf::Vector2f& getOriginCollision();

  void setTexture(const sf::Texture &texture);
  virtual bool update();
  virtual void noUpdate(); /*Change the entity when is not updated*/

  virtual void putIn(sf::Packet& packet) const;
  virtual void putOut(sf::Packet& packet);
};

#endif
