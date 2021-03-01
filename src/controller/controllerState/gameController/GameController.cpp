#include "GameController.h"
#include <string>
#include <iostream>

GameController::GameController(int width, int height) : GameController(new sf::RenderWindow(sf::VideoMode(width, height), "Among Us")){}

GameController::GameController(sf::RenderWindow* window){
  this->window = window;
  this->view = new View(*this->window, this->window->getSize().x, this->window->getSize().y);
  this->model = new Model(*this->view);
  this->running = true;
  this->icon = new sf::Image();
  this->icon->loadFromFile("assets/icone/index.jpg");

  this->window->setVerticalSyncEnabled(true);
  this->window->setFramerateLimit(30);
  this->window->setIcon(this->icon->getSize().x, this->icon->getSize().y, this->icon->getPixelsPtr());
}

void GameController::checkEvents(){
    sf::Event event;
    while (this->window->pollEvent(event)) {

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
       this->closeController();
     }
   }
}

void GameController::start(){
  this->running = true;
  this->run();
}

void GameController::run(){
  while(this->running){
    this->checkEvents();
    this->model->update();
    this->model->render();
  }
}

void GameController::closeController(){
  this->running = false;
}

unsigned int GameController::getId(){
  return GameController::id;
}

GameController::~GameController(){
  delete this->view;
  delete this->icon;
  delete this->model;
}
