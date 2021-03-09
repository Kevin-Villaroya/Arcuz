#ifndef __MENU_IP_CONTROLLER
#define __MENU_IP_CONTROLLER

#include "../../Controller.h"
#include "../../../model/modelMenuIp/ModelMenuIp.h"
#include "../../../viewer/view/View.h"
#include <string>

class MenuIpController : public Controller{
    private:
        unsigned int nextIdScreen = 0;

        ModelMenuIp* model;
        View* view;
    public:
        MenuIpController(sf::RenderWindow* window);
        MenuIpController(int width, int height);

        static const unsigned int id = 5;

        virtual void checkEvents();

        virtual void needToStart(std::vector<void*> parameters) override;
        virtual bool hasToSendWhenClose() override;
        virtual std::vector<void*> sendWhenClose() override;

        virtual void start() override;
        void run();

        virtual void closeController() override;
        virtual unsigned int getId() override;
        virtual unsigned int nextId() override;

        ~MenuIpController();
};

#endif