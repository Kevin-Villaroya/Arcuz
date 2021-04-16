#ifndef __MINIMAP_H__
#define __MINIMAP_H__

#include "../HudComponent.h"
#include "../../../../tool/SpriteTool.h"
#include "../model/entities/EntityDrawable.h"
#include "../model/entities/entitiesAnimated/character/Character.h"
#include <vector>

class Minimap : public HudComponent{
private:
	sf::View viewMinimap;
	sf::Sprite cadre;

	static const sf::FloatRect MINIMAP_IN_TEXTURE;
	static const sf::FloatRect BUTTON_PLUS_IN_TEXTURE;
	static const sf::FloatRect BUTTON_MINUS_IN_TEXTURE;

	sf::FloatRect plusButton;
	sf::FloatRect minusButton;

	sf::RectangleShape rectangleBackground;

	float scaleZoom;

	void increaseZoom();
	void decreaseZoom();

	void initBlackBackground(float posX, float posY, float sizeX, float sizeY);
	void initMinimapView(float posX, float posY, float sizeX, float sizeY);

	sf::RenderWindow* window;
public:
	Minimap(float posX, float posY, float sizeX, float sizeY, sf::RenderWindow* window);

	void click(float x, float y);

	bool plusButtonPressed(float x, float y);
	bool minusButtonPressed(float x, float y);

	void drawMap(const Character &character, const std::vector<sf::Drawable*> &entities);

	std::vector<sf::Drawable*> elementsToRender() override;
};

#endif