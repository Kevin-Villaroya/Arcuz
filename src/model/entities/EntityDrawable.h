#ifndef __ENTITY_DRAWABLE_H__
#define __ENTITY_DRAWABLE_H__

#include <SFML/Graphics/Sprite.hpp>

enum Direction{
  left,
  right,
  up,
  down
};

class EntityDrawable : public sf::Sprite{
protected:
  Direction direction;

  bool isSpriteFixe;
public:
  EntityDrawable();
  EntityDrawable(bool isSpriteFixe);

  unsigned int getPosX() const;
  unsigned int getPosY() const;

  unsigned int getHeight() const;
  unsigned int getWidth() const;

  virtual void watchDirection();
  void setOriginCenter();

  void setTexture(const sf::Texture &texture);
  virtual void update();
};

#endif
