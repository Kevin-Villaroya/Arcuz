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
  sf::SocketSelector selector;

  sf::Thread thread;
  sf::Mutex mutex;
  
  bool connectionSucceed;

  bool threadTerminated;
  bool threadPriority;

  unsigned short port;
  unsigned short portHost;

  unsigned int numberOfConnectionAttempts = 0;

  void setNetwork();

  bool connectGame();
  void disconnectGame();

  bool confirmationOfConnection();
  void confirmUpdate();

  void WhenNoUpdateReceived();

  void receiveMap();
public:
  static const unsigned int id = 2;
  
  NetworkClient(int width, int height, std::string ip, unsigned short port);
  NetworkClient(sf::RenderWindow* window);

  void start() override;
  void checkEvents() override;

  virtual void needToStart(std::vector<void*> parameters) override;

  void send(sf::Packet &packet);
  sf::Socket::Status receive(sf::Packet &packet);

  /*Recover data of server for update the client*/
  void updateCLient();
  /*Send data to server for update the server*/
  void updateServer();

  EntityDrawable* createEntity(sf::Packet& packet);
  unsigned int getId();
};

#endif
