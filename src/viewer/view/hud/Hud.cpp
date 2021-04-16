#include "Hud.h"
#include <iostream>

Hud::Hud(sf::RenderWindow* window) : sf::View(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y)){
	this->window = window;

	this->invokeAllElements();
}

void Hud::invokeAllElements(){
	float sizeX = this->window->getSize().x;
	float sizeY = this->window->getSize().y;
	this->minimap = new Minimap(0.74f * sizeX, 0.01f * sizeY, 0.25f * sizeX,0.25f * sizeY, this->window);
}

void Hud::render(const Character &character, const std::vector<sf::Drawable*> &entities){

	this->window->setView(*this);
	this->minimap->drawMap(character, entities);
	this->window->setView(*this);

	std::vector<sf::Drawable*> elements = this->minimap->elementsToRender();

	for(unsigned int i = 0; i < elements.size(); i++){
		this->window->draw(*elements[i]);
	}
}

void Hud::click(float x, float y){
	this->minimap->click(x, y);
}

Hud::~Hud(){
	//delete this->minimap;
}