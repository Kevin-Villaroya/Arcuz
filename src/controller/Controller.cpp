#include "Controller.h"

bool Controller::isRunning(){
    return this->running;
}

void Controller::needToStart(std::vector<void*> objectNeed){}

std::vector<void*> Controller::sendWhenClose(){
    return std::vector<void*>();
}

Controller::~Controller(){}