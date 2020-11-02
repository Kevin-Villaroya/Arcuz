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
public:
  EntityDrawable();

  unsigned int getPosX();
  unsigned int getPosY();

  unsigned int getLenght() const;
  unsigned int getWidth() const;

  void watchDirection();
  void setOriginCenter();

  virtual void update();
};

#endif
