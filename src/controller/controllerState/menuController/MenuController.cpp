#include "MenuController.h"
#include <iostream>

MenuController::MenuController(int width, int height) : MenuController(new sf::RenderWindow(sf::VideoMode(width, height), "Among Us")){}

MenuController::MenuController(sf::RenderWindow* window) {
    this->window = window;
    this->view = new View(*this->window, this->window->getSize().x, this->window->getSize().y);
    this->model = new ModelMenu(*this->view);
}

void MenuController::checkEvents(){
    sf::Event event;
    while (this->window->pollEvent(event)) {

        
        if(event.type == sf::Event::TextEntered && this->model->nicknameIsUpdating()){
            this->model->changeNickname(event.text.unicode);
        }else if (event.type == sf::Event::MouseButtonPressed){
            if (event.mouseButton.button == sf::Mouse::Left){
                this->model->clickOnMenu(event.mouseButton.x, event.mouseButton.y);
            }
        }else if(event.type == sf::Event::Closed){ // IF WINDOWS CLOSE
            this->closeController();
        }
   }
}

void MenuController::start(){
    this->running = true;
    this->run();
}

void MenuController::run(){
    while(this->running){
        this->checkEvents();
        this->model->update();
        this->model->render();
    }
}

void MenuController::closeController(){
    this->running = false;
}

unsigned int MenuController::getId(){
    return MenuController::id;
}

 MenuController::~MenuController(){
   delete this->view;
   delete this->model;
 }