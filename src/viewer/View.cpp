#include "View.h"

View::View(sf::RenderWindow &window, int height, int width): window(window){
  this->height = height;
  this->width = width;
}

void View::render(const std::vector<EntityDrawable> &entities){
  this->window.clear(sf::Color::Black);

  for(int i = 0; i < entities.size(); i++){
    this->window.draw(entities[i]);
  }

  this->window.display();
}
