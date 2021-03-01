#include "tool/mainFunctions/functionsInitGame.h"
#include "tool/mainFunctions/functionsLaunchGame.h"

#include "controller/ControllerManager.h"
#include "controller/controllerState/gameController/GameController.h"
#include "controller/controllerState/menuController/MenuController.h"
#include <string>
#include <cstring>

int main(int argc, char* argv[]){
    int width = 920;
    int height = 680;

    bool isMulti = initIsMulti();
    bool isHost = initIsHost();
    std::string ip = initIp();
    int port = initPort();

    if(argc == 2){
      if(strcmp(argv[1], "-h") == 0){
        isHost = true;
      }else if(strcmp(argv[1], "-c") == 0){
        isHost = false;
      }
    }

    ControllerManager manager;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(width, height), "Among Us");
    
    manager.add(new GameController(window)); //solo
    manager.add(new MenuController(window));
   

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
