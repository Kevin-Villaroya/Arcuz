#include "Controller.h"
#include <string>
#include <iostream>

Controller::Controller(int width, int height)  : window(sf::VideoMode(width, height), "Among Us"){
  this->view = new View(this->window, width, height);
  this->model = new Model(*this->view);
  this->running = true;
  this->window.setVerticalSyncEnabled(true);
  this->window.setFramerateLimit(60);
}

void Controller::checkEvents(){
    sf::Event event;
    while (this->window.pollEvent(event)) {

     if (event.type == sf::Event::KeyPressed){ //ANY KEY PRESSED

       if(event.key.shift){ //SHIFT PRESSED
         if(event.key.code == sf::Keyboard::Right){
           this->model->getMainCharacter()->run(Direction::right);
         }else if(event.key.code == sf::Keyboard::Left){
           this->model->getMainCharacter()->run(Direction::left);
         }else if(event.key.code == sf::Keyboard::Up){
           this->model->getMainCharacter()->run(Direction::up);
         }else if(event.key.code == sf::Keyboard::Down){
           this->model->getMainCharacter()->run(Direction::down);
         }
       }

       else if (event.key.code == sf::Keyboard::Escape){ //CASE ELSE
         this->running = false;
       }else if(event.key.code == sf::Keyboard::Right){
         this->model->getMainCharacter()->walk(Direction::right);
       }else if(event.key.code == sf::Keyboard::Left){
         this->model->getMainCharacter()->walk(Direction::left);
       }else if(event.key.code == sf::Keyboard::Up){
         this->model->getMainCharacter()->walk(Direction::up);
       }else if(event.key.code == sf::Keyboard::Down){
         this->model->getMainCharacter()->walk(Direction::down);
       }else{
         if(this->model->getMainCharacter()->getSpeed() != 0){
           this->model->getMainCharacter()->stop();
         }
       }
     }else{ // IF NO KEY PRESSED
       this->model->getMainCharacter()->stop();
     }

     if(event.type == sf::Event::Closed){ // IF WINDOWS CLOSE
       this->closeGame();
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
