#include "View.h"

View::View(sf::RenderWindow &window, int height, int width): window(window) , viewCharacter(sf::FloatRect(200.f, 200.f, 300.f, 200.f)){
  this->height = height;
  this->width = width;
}

void View::render(const Character &character, const std::vector<EntityDrawable> &entities){
  this->window.clear(sf::Color::Black);

  this->centerViewOn(character);

  for(unsigned int i = 0; i < entities.size(); i++){
    this->window.draw(entities[i]);
  }
  this->window.draw(character);
  this->window.display();
}

void View::centerViewOn(const Character &character){
  this->viewCharacter.setCenter(character.getPosX(), character.getPosY());
  this->window.setView(this->viewCharacter);
}
