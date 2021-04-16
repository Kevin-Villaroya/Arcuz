#ifndef __NETWORK_SERVER_H__
#define __NETWORK_SERVER_H__

#include <string>
#include <SFML/Network.hpp>
#include <SFML/Network/Packet.hpp>
#include <vector>
#include "../GameController.h"
#include "data/NetworkData.h"
#include "data/ClientInformation.h"

class NetworkServer : public GameController{
private:
  unsigned short port;
  sf::UdpSocket socket;
  std::vector<ClientInformation> clients;

  sf::Thread threadServer;
  sf::Mutex mutex;

  bool allClientupdated;

  void processingRequest(const sf::IpAddress &adressClient, unsigned short port, sf::Packet &packet);

  unsigned int connectClient(const sf::IpAddress &adressClient, unsigned short port, sf::Packet& packet);
  void notAcceptClient(const sf::IpAddress &adressClient, unsigned short port);

  void updateAllCLient(std::vector<EntityDrawable*> &entitiesUpdated);
  void sendUpdateTo(ClientInformation &client, const std::vector<EntityDrawable*> &entities);
  void updateCLient(sf::Packet& packet);

  unsigned int confirmationOfConnection(const sf::IpAddress &adressClient, unsigned short port);
  void confirmationOfHavingReceivedUpdate(int uid);

  void sendMapTo(ClientInformation& client);
public:
  static const unsigned int id = 3;
  
  NetworkServer(int width, int height, unsigned short port);
  NetworkServer(sf::RenderWindow* window);

  void startServer();
  void initStart();
  void start() override;

  virtual void needToStart(std::vector<void*> parameters) override;

  void deleteClient(sf::IpAddress ip, unsigned short port);
  ClientInformation& addCLient(sf::IpAddress ip, unsigned short port, unsigned int uid);

  bool clientActive(ClientInformation &client);

  bool addCharacterClient(std::string& name, TypeCharacter& type, unsigned int uid);
  void removeCharacterClient(const sf::IpAddress &adressClient, unsigned short port, const std::string& name);

  unsigned int getId() override;
};

#endif
