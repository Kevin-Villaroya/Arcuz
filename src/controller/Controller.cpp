#include "Controller.h"
#include <string>
#include <iostream>

Controller::Controller(int width, int height)  : window(sf::VideoMode(width, height), "Among Us"){
  this->view = new View(this->window, width, height);
  this->model = new Model(*this->view);
  this->running = true;
}

void Controller::checkEvents(){ //if event do something to model TODO
   sf::Event event;
   this->window.pollEvent(event);
   if (event.type == sf::Event::KeyPressed){
     if (event.key.code == sf::Keyboard::Escape){
       this->running = false;
     }
   }
}

void Controller::start(){
  while(this->running){
    this->checkEvents();
    this->model->update();
    this->model->render();
  }
}

void Controller::closeGame(){
  this->running = false;
}

Controller::~Controller(){
  delete this->view;
  delete this->model;
}
