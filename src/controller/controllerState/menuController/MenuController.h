#ifndef __MENU_H__
#define __MENU_H__

#include "../../Controller.h"
#include "../../../model/modelMenu/ModelMenu.h"
#include <string>

class MenuController : public Controller{
private:
    unsigned int nextIdScreen = 0;

    ModelMenu* model;
    View* view;
    
public:
    MenuController(sf::RenderWindow* window);
    MenuController(int width, int height);

    static const unsigned int id = 4;

    virtual void checkEvents();

    virtual void start();
    void run();

    virtual bool hasToSendWhenClose() override;
    virtual std::vector<void*> sendWhenClose() override;

    virtual void closeController();

    virtual unsigned int getId();
    virtual unsigned int nextId() override;

    ~MenuController();
};

#endif