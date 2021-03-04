//#include "tool/mainFunctions/functionsInitGame.h"
//#include "tool/mainFunctions/functionsLaunchGame.h"

#include "controller/ControllerManager.h"
#include "controller/controllerState/gameController/GameController.h"
#include "controller/controllerState/gameController/network/NetworkClient.h"
#include "controller/controllerState/gameController/network/NetworkServer.h"
#include "controller/controllerState/menuController/MenuController.h"
#include <string>
#include <cstring>

int main(int argc, char* argv[]){
    int width = 1080;
    int height = 1080;

    /*bool isMulti = initIsMulti();
    bool isHost = initIsHost();
    std::string ip = initIp();
    int port = initPort();

    if(argc == 2){
      if(strcmp(argv[1], "-h") == 0){
        isHost = true;
      }else if(strcmp(argv[1], "-c") == 0){
        isHost = false;
      }
    }*/

    ControllerManager manager;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(width, height), "Arcuz");
    
    manager.add(new MenuController(window)); // menu 4
    manager.add(new GameController(window)); //solo 1
    manager.add(new NetworkClient(window)); //client 2
    //manager.add(new NetworkServer(window)); //host 3

    manager.start();

    /*
    ControllerManager manager;
    manager.add(new GameController(width, height));
    manager.add(new MenuController(width, height));
    manager.add(new ConfigGameController(width, height));
    
    manager.start();
    */

    /*if(!isMulti){
      launchSolo(width, height);
    }else if(isHost){
      launchServer(width, height, port);
    }else{
      launchClient(width, height, ip, port);
    }*/

    return 0;
}
