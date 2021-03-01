#ifndef __SOCKET_H__
#define __SOCKET_H__

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

  bool allClientupdated;

  void processingRequest(const sf::IpAddress &adressClient, unsigned short port, sf::Packet &packet);

  unsigned int connectClient(const sf::IpAddress &adressClient, unsigned short port, sf::Packet& packet);
  void notAcceptClient(const sf::IpAddress &adressClient, unsigned short port);

  void updateAllCLient(std::vector<EntityDrawable*> &entitiesUpdated);
  void sendUpdateTo(ClientInformation &client, const std::vector<EntityDrawable*> &entities);
  void updateCLient(sf::Packet& packet);

  unsigned int confirmationOfConnection(const sf::IpAddress &adressClient, unsigned short port);
  void confirmationOfHavingReceivedUpdate(int uid);
public:
  NetworkServer(int width, int height, unsigned short port);
  void startServer();
  void start() override;

  void deleteClient(sf::IpAddress ip, unsigned short port);
  ClientInformation& addCLient(sf::IpAddress ip, unsigned short port, unsigned int uid);

  bool clientActive(ClientInformation &client);

  bool addCharacterClient(std::string& name, TypeCharacter& type, unsigned int uid);
  void removeCharacterClient(const sf::IpAddress &adressClient, unsigned short port, const std::string& name);
};

#endif
