#ifndef __MENU_H__
#define __MENU_H__

#include "../../Controller.h"
#include "../../../model/modelMenu/ModelMenu.h"
#include <string>

class MenuController : public Controller{
private:
    static const unsigned int id = 0;

    std::string nameCharacter;

    ModelMenu* model;
    View* view;

    bool online;
    bool host;
public:
    MenuController(sf::RenderWindow* window);
    MenuController(int width, int height);

    virtual void checkEvents();

    virtual void start();
    void run();

    virtual void closeController();

    virtual unsigned int getId();

    ~MenuController();
};

#endif