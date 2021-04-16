#ifndef __HUD_H__
#define __HUD_H__

#include <SFML/Graphics.hpp>
#include "hudComponent/HudComponent.h"
#include "hudComponent/minimap/Minimap.h"

class Hud : public sf::View{
private:
	sf::RenderWindow* window;

	Minimap* minimap;

	void invokeAllElements();
public:
	Hud(sf::RenderWindow* window);

	void render(const Character &character, const std::vector<sf::Drawable*> &entities);
	void click(float x, float y);
	~Hud();
};


#endif