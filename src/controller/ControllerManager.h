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

        void run();

        void getController(unsigned int id);

        ~ControllerManager();
};


#endif