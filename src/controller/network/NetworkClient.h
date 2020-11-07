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

  unsigned int port;
public:
  NetworkClient(int width, int height, std::string ip, unsigned int port);
  void communicate(sf::Packet &packet);
  bool connect();
  void send(sf::Packet &packet);
};

#endif
