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
  std::cout << "Server Ready" << std::endl;
  std::cout << "listening on port: " << port <<std::endl;

  NetworkServer* controller = new NetworkServer(width, height, port);
  sf::Thread threadServer(&NetworkServer::startServer, controller);
  threadServer.launch();

  controller->start();
  threadServer.terminate();
  delete controller;
}

void launchClient(int width, int height, std::string ip , int port){
  std::cout << "Client ready" << std::endl;
  std::cout << "Server Location: ip: " << ip << ", port: "<< port <<std::endl;

  NetworkClient* controller = new NetworkClient(width, height, ip, port);
  controller->start();
  delete controller;
}
