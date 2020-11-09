#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <string>
#include <SFML/Network.hpp>
#include <SFML/Network/Packet.hpp>
#include <vector>
#include "../Controller.h"

class NetworkServer : public Controller{
private:
  unsigned int port;
  sf::TcpListener listener;
  sf::SocketSelector selector;
  std::vector<sf::TcpSocket*> clients;

  void processingRequest(sf::TcpSocket &socket, sf::Packet &packet);
public:
  NetworkServer(int width, int height, unsigned int port);
  void startServer();
  void updateAllCLient();
};

#endif
