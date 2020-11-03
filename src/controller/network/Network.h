#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "../Controller.h"
#include <string>
#include <SFML/Network.hpp>

class Network : public Controller{
private:
  sf::IpAddress ip;
  unsigned int port;
  bool host;

  sf::TcpSocket socket;
  sf::TcpListener listener;

  void setUpConnection();
public:
  Network(unsigned int width, unsigned int height);

};

sf::IpAddress initIp(); //needed for set IP in constructor
unsigned int initPort(); //needed for set IP in constructor

#endif
