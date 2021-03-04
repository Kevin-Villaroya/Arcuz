#include "ControllerManager.h"

void ControllerManager::add(Controller* controller){
    this->controllers.push_back(controller);
}

void ControllerManager::start(){
    if(this->controllers.size() > 0){
        this->currentController = this->controllers[0];
    }
    this->run();
}

void ControllerManager::run(){
    this->currentController->start();
    while(this->currentController->nextId() != 0){
        this->getController(this->currentController->nextId());
        this->currentController->start();
    }
}

void ControllerManager::getController(unsigned int id){
    for(unsigned int i = 0; i < this->controllers.size(); i++){
        if(this->controllers[i]->getId() == id){
            this->currentController = this->controllers[i];
        }
    }
}

ControllerManager::~ControllerManager(){
    for(unsigned int i = 0; i < this->controllers.size(); i++){
        delete this->controllers[i];
    }
}