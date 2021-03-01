#ifndef __CONTROLLER_MANAGER_H__
#define __CONTROLLER_MANAGER_H__

#include <vector>
#include "Controller.h"

class ControllerManager{
    private:
        std::vector<Controller*> controllers;
        Controller* currentController;

    public:
        void add(Controller* controller);
        void start();

        ~ControllerManager();
};


#endif