#include <functional>
#include "../../controller/Controller.h"
#include "../../controller/network/NetworkClient.h"
#include "../../controller/network/NetworkServer.h"

void launchSolo(int width, int height){
  Controller* controller = new Controller(width, height);
  std::cout << "config.ini loaded" << std::endl;
  std::cout << "game solo launched" << std::endl;
  controller->start();
  delete controller;
}

void launchServer(int width, int height, int port){
  NetworkServer* controller = new NetworkServer(width, height, port);
  sf::Thread threadServer(&NetworkServer::startServer, controller);
  threadServer.launch();

  std::cout << "Server Ready" << std::endl;
  std::cout << "listening on port: " << port <<std::endl;
  controller->start();
  threadServer.terminate();
  delete controller;
}

void launchClient(int width, int height, std::string ip , int port){
  NetworkClient* controller = new NetworkClient(width, height, ip, port);

  std::cout << "Client ready" << std::endl;
  std::cout << "Server Location: ip: " << ip << ", port: "<< port <<std::endl;
  controller->start();
  delete controller;
}
