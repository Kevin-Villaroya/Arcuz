#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <SFML/Graphics.hpp>

class Controller{
    protected:
        unsigned int idNextScreen;
        bool running;

        sf::RenderWindow* window; //WINDOWS IN SFML ARE DISPLAYERS AND LISTENERS
    public:
        virtual void needToStart(std::vector<void*> parameters);
        virtual bool hasToSendWhenClose() = 0;
        virtual std::vector<void*> sendWhenClose();

        virtual void start() = 0;
        virtual void closeController() = 0;

        bool isRunning();
        virtual unsigned int getId() = 0;
        virtual unsigned int nextId() = 0;
        virtual ~Controller();
};


#endif