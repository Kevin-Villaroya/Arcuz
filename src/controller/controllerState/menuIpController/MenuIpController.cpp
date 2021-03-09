#include "MenuIpController.h"
#include <iostream>

MenuIpController::MenuIpController(sf::RenderWindow* window){
    this->window = window;
    this->view = new View(*this->window, this->window->getSize().x, this->window->getSize().y);
    this->model = new ModelMenuIp(*this->view);
}

MenuIpController::MenuIpController(int width, int height) : MenuIpController(new sf::RenderWindow(sf::VideoMode(width, height), "Arcuz")){}

void MenuIpController::checkEvents(){
    sf::Event event;
    while (this->window->pollEvent(event)) {
        if(event.type == sf::Event::TextEntered && event.text.unicode < 128){
            this->model->changeValue((char)event.text.unicode);
        }else if (event.type == sf::Event::MouseButtonPressed){
            if (event.mouseButton.button == sf::Mouse::Left){
                int idController = this->model->clickOnMenu(event.mouseButton.x, event.mouseButton.y);
                if(idController != 0){
                    this->nextIdScreen = idController;
                    this->closeController();
                }
            }
        }else if(event.type == sf::Event::KeyPressed){
            if (event.key.code == sf::Keyboard::Escape){
                this->nextIdScreen = 4;
                this->closeController();
            }
        }else if(event.type == sf::Event::Closed){ // IF WINDOWS CLOSE
            this->closeController();
        }
   }
}

void MenuIpController::needToStart(std::vector<void*> parameters){
    std::string nameCharacter = *(std::string*)(parameters[0]);
    bool host = *(bool*)(parameters[1]);
    this->model->setNameCharacter(nameCharacter);
    this->model->setIsHost(host);
}

bool MenuIpController::hasToSendWhenClose(){
    if(this->nextIdScreen == 2 || this->nextIdScreen == 3){
        return true;
    }else{
        return false;
    }
}

std::vector<void*> MenuIpController::sendWhenClose(){
    std::vector<void*> parameters;

    parameters.push_back(&this->model->getNameCharacter());

    if(this->nextIdScreen == 2){ //client
        parameters.push_back(&this->model->getPort());
        parameters.push_back(&this->model->getIp());
    }else if(this->nextIdScreen == 3){ //host
        parameters.push_back(&this->model->getPort());
    }
    return parameters;
}

void MenuIpController::start(){
    this->nextIdScreen = 0;
    this->running = true;
    this->run();
}

void MenuIpController::run(){
    while(this->running){
        this->checkEvents();
        this->model->update();
        this->model->render();
    }
}

void MenuIpController::closeController(){
    this->running = false;
}

unsigned int MenuIpController::getId(){
    return MenuIpController::id;
}

unsigned int MenuIpController::nextId(){
    return nextIdScreen;
}

MenuIpController::~MenuIpController(){
delete this->view;
delete this->model;
}