#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <string>
#include <SFML/Network.hpp>
#include <SFML/Network/Packet.hpp>
#include <vector>
#include "../Controller.h"
#include "data/NetworkData.h"

class NetworkServer : public Controller{
private:
  unsigned int port;
  sf::TcpListener listener;
  sf::SocketSelector selector;
  std::vector<sf::TcpSocket*> clients;

  void processingRequest(sf::TcpSocket &socket, sf::Packet &packet);

  void connectClient(sf::TcpSocket &socket, const NetworkData &data);
  void updateAllCLient();
public:
  NetworkServer(int width, int height, unsigned int port);
  void startServer();
  void start() override;

  void addCharacterClient(std::string name);
  void clientWalk(sf::TcpSocket &socket, Direction direction);
};

#endif
