#include "MenuController.h"

MenuController::MenuController(int width, int height) : MenuController(new sf::RenderWindow(sf::VideoMode(width, height), "Among Us")){}

MenuController::MenuController(sf::RenderWindow* window) {
    this->window = window;
}

void MenuController::start(){
    this->running = true;
    this->run();
}

void MenuController::run(){
    while(this->running){
        /*this->checkEvents();
        this->model->update();
        this->model->render();*/
    }
}

void MenuController::closeController(){
    this->running = false;
}

unsigned int MenuController::getId(){
    return MenuController::id;
}