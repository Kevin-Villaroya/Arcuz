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
                int idController = this->model->clickOnMenu(event.mouseButton.x, event.mouseButton.y);
                if(idController != 0){
                    this->nextIdScreen = idController;
                    this->closeController();
                }
            }
        }else if(event.type == sf::Event::Closed){ // IF WINDOWS CLOSE
            this->closeController();
        }
   }
}

void MenuController::start(){
    this->nextIdScreen = 0;
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

bool MenuController::hasToSendWhenClose(){
    return true;
}

std::vector<void*> MenuController::sendWhenClose(){
    std::vector<void*> parameters;
    parameters.push_back(&this->model->getNameCharacter());
    parameters.push_back(&this->model->getSkin());

    if(this->nextId() == 5){
        parameters.push_back(&this->model->isHosting());
    }

    return parameters;
}

void MenuController::closeController(){
    this->running = false;
}

unsigned int MenuController::getId(){
    return MenuController::id;
}

unsigned int MenuController::nextId(){
    return this->nextIdScreen;
}

MenuController::~MenuController(){
delete this->view;
delete this->model;
}