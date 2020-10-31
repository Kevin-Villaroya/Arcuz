#include "Controller.h"

Controller::Controller(int width, int height, bool fullscreen){
  makeWindow(width, height, fullscreen);

  this->view = new View(this->window, width, height, fullscreen);
  this->model = new Model(*this->view);
  this->running = true;
}

void Controller::start(){
  while(this->running){
    this->window.display();
  }
}

void Controller::makeWindow(int width, int height, bool fullscreen){
  if(fullscreen){
    this->window.create(sf::VideoMode(width, height), "Among Us", sf::Style::Fullscreen);
  }else{
    this->window.create(sf::VideoMode(width, height), "Among Us");
  }
  this->window.setFramerateLimit( 60 );
}
