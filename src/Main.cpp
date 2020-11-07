#include "model/Model.h"
#include "controller/Controller.h"
#include "controller/network/NetworkClient.h"
#include "controller/network/NetworkServer.h"
#include "functionInitGame.h"

bool isHost();

int main(){
    Controller* controller;
    int width = 920;
    int height = 680;

    if(initIsHost()){
      controller = new NetworkServer(width, height, initPort());
    }else{
      controller = new NetworkClient(width, height, initIp(), initPort());
    }
    std::cout << "config.ini loaded" << std::endl;

    controller->start();
    delete controller;
    return 0;
}
