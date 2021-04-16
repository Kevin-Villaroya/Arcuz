#ifndef __HUD_COMPONENT_H__
#define __HUD_COMPONENT_H__

#include <vector>
#include <SFML/Graphics.hpp>

class HudComponent{
protected:
	float posX;
	float posY;

	float sizeX;
	float sizeY;
public:
	HudComponent(float posX, float posY, float sizeX, float sizeY);
	virtual std::vector<sf::Drawable*> elementsToRender() = 0;

};
#endif