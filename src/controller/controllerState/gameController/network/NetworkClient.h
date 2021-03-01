#ifndef __NETWORK_CLIENT_H__
#define __NETWORK_CLIENT_H__

#include <string>
#include <SFML/Network.hpp>
#include <SFML/Network/Packet.hpp>
#include <vector>
#include <iostream>
#include "../GameController.h"
#include "data/NetworkData.h"

class NetworkClient : public GameController{
private:
  sf::IpAddress ip;
  sf::UdpSocket socket;

  sf::Thread thread;
  sf::Mutex mutex;
  
  bool connectionSucceed;

  bool threadTerminated;
  bool threadPriority;

  unsigned short port;
  unsigned short portHost;

  bool connectGame();
  void disconnectGame();

  bool confirmationOfConnection();
  void confirmUpdate();

  void WhenNoUpdateReceived();
public:
  NetworkClient(int width, int height, std::string ip, unsigned short port);

  void start() override;
  void checkEvents() override;

  void send(sf::Packet &packet);
  sf::Socket::Status receive(sf::Packet &packet);

  /*Recover data of server for update the client*/
  void updateCLient();
  /*Send data to server for update the server*/
  void updateServer();

  EntityDrawable* createEntity(sf::Packet& packet);
};

#endif
