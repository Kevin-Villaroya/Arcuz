//#include "tool/mainFunctions/functionsInitGame.h"
//#include "tool/mainFunctions/functionsLaunchGame.h"

#include "controller/ControllerManager.h"
#include "controller/controllerState/gameController/GameController.h"
#include "controller/controllerState/gameController/network/NetworkClient.h"
#include "controller/controllerState/gameController/network/NetworkServer.h"
#include "controller/controllerState/menuController/MenuController.h"
#include "controller/controllerState/menuIpController/MenuIpController.h"
#include <string>
#include <cstring>

int main(int argc, char* argv[]){
    int width = 1080;
    int height = 1080;

    ControllerManager manager;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(width, height), "Arcuz");
    
    manager.add(new MenuController(window)); // menu 4
    manager.add(new MenuIpController(window)); // menuIp 5

    manager.add(new GameController(window)); //solo 1
    manager.add(new NetworkClient(window)); //client 2
    manager.add(new NetworkServer(window)); //host 3

    manager.start();
    return 0;
}
