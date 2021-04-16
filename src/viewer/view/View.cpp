#include "View.h"
#include <iostream>

View::View(sf::RenderWindow &window): View(window, 200, 200){}

View::View(sf::RenderWindow &window, int height, int width): window(window) , game(sf::FloatRect(width / 2, height / 2, width, height)), hud(&window){
  this->height = height;
  this->width = width;

  this->game.setViewport(sf::FloatRect(0.f,0.f,1.f,1.f));
}

void View::render(const Character &character, const std::vector<sf::Drawable*> &entities){
  this->window.clear(sf::Color::Black);

  this->centerViewOn(character);

  for(unsigned int i = 0; i < entities.size(); i++){
    this->window.draw(*entities[i]);
  }
  
  this->hud.render(character, entities);

  this->window.display();
}

void View::render(const std::vector<sf::Drawable*> &entities){
  this->window.clear(sf::Color::Black);

  this->centerViewOn((float)this->width / 2, (float)this->height / 2);

  for(unsigned int i = 0; i < entities.size(); i++){
    this->window.draw(*entities[i]);
  }

  this->window.display();
}

void View::centerViewOn(const Character &character){
  this->game.setCenter(character.getPosX(), character.getPosY());
  this->window.setView(this->game);
}

void View::centerViewOn(float x, float y){
  this->game.setCenter(x, y);
  this->window.setView(this->game);
}

const sf::Vector2f& View::getSize() const{
  return this->game.getSize();
}

const sf::Vector2u View::getSizeWindow() const{
  return this->window.getSize();
}

const sf::Vector2f& View::getCenter() const{
  return this->game.getCenter();
}

void View::setSize(float x, float y){
  this->game.setSize(sf::Vector2f(x, y));
}

void View::click(float x, float y){
  this->hud.click(x, y);
}