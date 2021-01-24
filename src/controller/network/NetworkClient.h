#ifndef __NETWORK_CLIENT_H__
#define __NETWORK_CLIENT_H__

#include <string>
#include <SFML/Network.hpp>
#include <SFML/Network/Packet.hpp>
#include <vector>
#include <iostream>
#include "../Controller.h"

class NetworkClient : public Controller{
private:
  sf::IpAddress ip;
  sf::TcpSocket socket;

  sf::Thread thread;
  bool threadTerminated;

  unsigned int port;
  void connectGame();
  void disconnectGame();

  void confirmationOfConnection();
public:
  NetworkClient(int width, int height, std::string ip, unsigned int port);
  void communicate(sf::Packet &packet);
  bool connectServer();
  void send(sf::Packet &packet);

  void updateCLient();
  void start() override;
  void checkEvents() override;

  EntityDrawable* createEntity(sf::Packet& packet);
};

#endif
