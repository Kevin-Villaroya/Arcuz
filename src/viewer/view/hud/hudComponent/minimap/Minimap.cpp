#include "Minimap.h"
#include "../../../../texture/MenuTexture.h"
#include <iostream>


const sf::FloatRect Minimap::MINIMAP_IN_TEXTURE = sf::FloatRect(15,43,368,339);
const sf::FloatRect Minimap::BUTTON_PLUS_IN_TEXTURE = sf::FloatRect(129,347,68,49);
const sf::FloatRect Minimap::BUTTON_MINUS_IN_TEXTURE = sf::FloatRect(203,347,68,49);

Minimap::Minimap(float posX, float posY, float sizeX, float sizeY, sf::RenderWindow* window) : HudComponent(posX, posY, sizeX, sizeY), viewMinimap(sf::FloatRect(0,0,sizeX,sizeY)), cadre(*MenuTexture::getCadreMinimap()){
	this->cadre.setPosition(posX, posY);
	this->cadre.setScale(sizeX / this->cadre.getTexture()->getSize().x, sizeY / this->cadre.getTexture()->getSize().y);

	this->window = window;
	this->scaleZoom = 2;

	this->initBlackBackground(posX, posY, sizeX, sizeY);
	this->initMinimapView(posX, posY, sizeX, sizeY);
}

std::vector<sf::Drawable*> Minimap::elementsToRender(){
	std::vector<sf::Drawable*> elements;

	elements.push_back(&this->filter);
	elements.push_back(&this->cadre);

	return elements;
}

void Minimap::click(float x, float y){
	this->plusButtonPressed(x, y);
	this->minusButtonPressed(x, y);
}

bool Minimap::plusButtonPressed(float x, float y){
	float xBegin = this->posX + Minimap::BUTTON_PLUS_IN_TEXTURE.left * this->cadre.getScale().x;
	float yBegin = this->posY + Minimap::BUTTON_PLUS_IN_TEXTURE.top * this->cadre.getScale().y;
	float xEnd = xBegin + Minimap::BUTTON_PLUS_IN_TEXTURE.width * this->cadre.getScale().x;
	float yEnd = yBegin + Minimap::BUTTON_PLUS_IN_TEXTURE.height * this->cadre.getScale().y;

	if(x > xBegin && x < xEnd && y > yBegin && y < yEnd){
		this->decreaseZoom();
		return true;
	} 
	return false;
}

bool Minimap::minusButtonPressed(float x, float y){
	float xBegin = this->posX + Minimap::BUTTON_MINUS_IN_TEXTURE.left * this->cadre.getScale().x;
	float yBegin = this->posY + Minimap::BUTTON_MINUS_IN_TEXTURE.top * this->cadre.getScale().y;
	float xEnd = xBegin + Minimap::BUTTON_MINUS_IN_TEXTURE.width * this->cadre.getScale().x;
	float yEnd = yBegin + Minimap::BUTTON_MINUS_IN_TEXTURE.height * this->cadre.getScale().y;

	if(x > xBegin && x < xEnd && y > yBegin && y < yEnd){
		this->increaseZoom();
		return true;
	} 
	return false;
}

void Minimap::drawMap(const Character &character, const std::vector<sf::Drawable*> &entities){
	this->window->draw(this->rectangleBackground);

	this->window->setView(this->viewMinimap);

	this->viewMinimap.setCenter(character.getPosX(), character.getPosY());

	for(unsigned int i = 0; i < entities.size(); i++){
	this->window->draw(*entities[i]);
	}

}

void Minimap::increaseZoom(){
	if(this->scaleZoom < 8){
		this->viewMinimap.zoom(1 / this->scaleZoom);
		this->scaleZoom++;
		this->viewMinimap.zoom(this->scaleZoom);
	}
}

void Minimap::decreaseZoom(){
	if(this->scaleZoom > 1){
		this->viewMinimap.zoom(1 / this->scaleZoom);
		this->scaleZoom--;
		this->viewMinimap.zoom(this->scaleZoom);
	}
}

void Minimap::initBlackBackground(float posX, float posY, float sizeX, float sizeY){
	float xBegin = this->posX + Minimap::MINIMAP_IN_TEXTURE.left * this->cadre.getScale().x;
	float yBegin = this->posY + Minimap::MINIMAP_IN_TEXTURE.top * this->cadre.getScale().y;
	float xEnd = xBegin + Minimap::MINIMAP_IN_TEXTURE.width * this->cadre.getScale().x;
	float yEnd = yBegin + Minimap::MINIMAP_IN_TEXTURE.height * this->cadre.getScale().y;

	this->rectangleBackground = sf::RectangleShape(sf::Vector2f(xEnd - xBegin, yEnd - yBegin));
	this->rectangleBackground.setPosition(xBegin, yBegin);
	this->rectangleBackground.setFillColor(sf::Color::Black);

	this->filter = sf::RectangleShape(sf::Vector2f(xEnd - xBegin, yEnd - yBegin));
	this->filter.setPosition(xBegin, yBegin);
	this->filter.setFillColor(sf::Color(0,0,0,50));
}

void Minimap::initMinimapView(float posX, float posY, float sizeX, float sizeY){
	float posXPercent = (posX + Minimap::MINIMAP_IN_TEXTURE.left * this->cadre.getScale().x) / this->window->getSize().x;
	float posYPercent = (posY + Minimap::MINIMAP_IN_TEXTURE.top * this->cadre.getScale().y) / this->window->getSize().y;
	float sizeXPercent = Minimap::MINIMAP_IN_TEXTURE.width * this->cadre.getScale().x / this->window->getSize().x;
	float sizeYPercent = Minimap::MINIMAP_IN_TEXTURE.height * this->cadre.getScale().y / this->window->getSize().y;
	
	this->viewMinimap.setViewport(sf::FloatRect(posXPercent, posYPercent, sizeXPercent, sizeYPercent));
	this->viewMinimap.zoom(this->scaleZoom);
}