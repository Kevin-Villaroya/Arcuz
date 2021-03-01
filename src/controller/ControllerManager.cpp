#include "ControllerManager.h"

void ControllerManager::add(Controller* controller){
    this->controllers.push_back(controller);
}

void ControllerManager::start(){
    if(this->controllers.size() > 0){
        this->controllers[0]->start();
    }
}

ControllerManager::~ControllerManager(){
    for(unsigned int i = 0; i < this->controllers.size(); i++){
        delete this->controllers[i];
    }
}