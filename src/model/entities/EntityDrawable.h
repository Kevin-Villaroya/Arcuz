#ifndef __ENTITY_DRAWABLE_H__
#define __ENTITY_DRAWABLE_H__

#include <SFML/Graphics/Sprite.hpp>

class EntityDrawable : public sf::Sprite{
private:

public:
  unsigned int getPosX();
  unsigned int getPosY();
};

#endif
