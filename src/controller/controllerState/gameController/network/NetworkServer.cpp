#include "NetworkServer.h"
#include <iostream>
#include <vector>
#include <typeinfo>
#include <string.h>
#include <../../model/entities/EntityDrawable.h>

NetworkServer::NetworkServer(int width, int height, unsigned short port) : GameController(width, height), threadServer(&NetworkServer::startServer, this){
    this->port = port;
    this->socket.bind(this->port);
    this->allClientupdated = false;
}

NetworkServer::NetworkServer(sf::RenderWindow* window) : GameController(window), threadServer(&NetworkServer::startServer, this){

}

void NetworkServer::startServer(){
  while (true){
    sf::IpAddress sender;
    unsigned short port;

    sf::Packet packet;

    if (this->socket.receive(packet, sender, port) != sf::Socket::Done){
      //std::cout << "Erreur" << std::endl;
    }else{
      this->processingRequest(sender, port, packet);
    }
  }
}

void NetworkServer::initStart(){
  std::cout << "Server Ready" << std::endl;
  std::cout << "listening on port: " << port <<std::endl;

  this->socket.bind(this->port);
  this->allClientupdated = false;

  threadServer.launch();
}

void NetworkServer::start(){
  while(this->running){
    this->checkEvents();
    this->model->update();
    this->model->render();
    if(!allClientupdated && this->model->updateNeededForEntities()){
      this->updateAllCLient(this->model->getEntitiesNeedUpdate());
    }
  }
  threadServer.terminate();
}

void NetworkServer::needToStart(std::vector<void*> parameters){
  std::string nameCharacter = *(std::string*)(parameters[0]);
  unsigned short port = *(unsigned short*)(parameters[1]);

  this->port = port;
  this->model->getMainCharacter()->setName(nameCharacter);

  this->initStart();
}

void NetworkServer::processingRequest(const sf::IpAddress &adressClient, unsigned short port, sf::Packet &packet){
  uint32_t action_int;
  Action action;
  std::string name;
  unsigned int uid;

  packet >> action_int;
  action = (Action)action_int;

  if(action == Action::connect){
    uid = this->connectClient(adressClient, port, packet);
    if(uid != 0){
      this->addCLient(adressClient, port, uid);
    }else{
      this->notAcceptClient(adressClient, port);
    }
  }else if (action == Action::disconnect){
    packet >> name;
    if(this->model->existEntity(name)){
      this->removeCharacterClient(adressClient, port, name);
    }
    this->deleteClient(adressClient, port);
  }else if (action == Action::update){
    this->updateCLient(packet);
  }else if(action == Action::confirm_update){
    packet >> uid;
    this->confirmationOfHavingReceivedUpdate(uid);
  }
}

void  NetworkServer::updateAllCLient(std::vector<EntityDrawable*> &entitiesUpdated){
  this->allClientupdated = true;
  std::vector<EntityDrawable*> entitiesTemp;

  for(unsigned int i = 0; i < this->clients.size(); i++){
    if(this->clientActive(this->clients[i])){
      entitiesTemp.clear();
      for(unsigned int j = 0; j < entitiesUpdated.size(); j++){
        if(entitiesUpdated[j]->getUid() != this->clients[i].uid){
          entitiesTemp.push_back(entitiesUpdated[j]);
        }
      }
      sendUpdateTo(this->clients[i], entitiesTemp);
    }  
  }
  this->allClientupdated = false;
}

void NetworkServer::sendUpdateTo(ClientInformation &client, const std::vector<EntityDrawable*> &entities){
  sf::Packet packet;
  unsigned int size = (unsigned int)entities.size();
  packet << size;
  for(unsigned int i = 0; i < size; i++){
    if(entities[i]->getUid() != client.uid){
      packet << entities[i]->getUid();
      packet << entities[i]->getIndexTypeEntity();
      entities[i]->putIn(packet);
    }
  }
  this->socket.send(packet, client.ip, client.port);
  client.nbUpdateNotConfirmed +=1;
}

void NetworkServer::updateCLient(sf::Packet& packet){
  int uid = -1;
  packet >> uid;

  EntityDrawable* character = this->model->getEntity(uid);

  if(uid != -1){
    character->putOut(packet);
  }
}

unsigned int  NetworkServer::connectClient(const sf::IpAddress &adressClient, unsigned short port, sf::Packet& packet){
  std::string name;
  uint32_t type_int;
  TypeCharacter type;
  unsigned int uid = 0;

  packet >> name;
  packet >> type_int;
  type = (TypeCharacter)type_int;

  std::cout << "le joueur " << name << " essaie de se connecter" << std::endl;

  if(!this->model->existEntity(name)){
      uid = this->confirmationOfConnection(adressClient, port);
      ClientInformation client = this->addCLient(adressClient, port, uid);

      std::vector<EntityDrawable*> entitiesToSend = this->model->getEntities();
      entitiesToSend.push_back(this->model->getMainCharacter());

      this->sendUpdateTo(client, entitiesToSend);
      this->addCharacterClient(name, type, uid);
    }else{
      std::cout << "le joueur " << name << " existe déja ERREUR" << std::endl;
      this->notAcceptClient(adressClient, port);
    }

    return uid;
}

void NetworkServer::notAcceptClient(const sf::IpAddress &adressClient, unsigned short port){
  sf::Packet packet;
  packet << (uint32_t)Action::confirm_disconnect;

  this->socket.send(packet, adressClient, port);
}

unsigned int NetworkServer::confirmationOfConnection(const sf::IpAddress &adressClient, unsigned short port){
  sf::Packet packetSend;
  unsigned int uid = this->model->quantityOfEntities() + 1;

  packetSend << uid;
  this->socket.send(packetSend, adressClient, port);
  return uid;
}

void NetworkServer::confirmationOfHavingReceivedUpdate(int uid){
  bool find = false;
  for(unsigned int i = 0; i < this->clients.size() && !find; i++){
    if(this->clients[i].uid == uid){
      this->clients[i].state = State::active;
      this->clients[i].nbUpdateNotConfirmed = 0;
      find = true;
    }
  }
}

void NetworkServer::deleteClient(sf::IpAddress ip, unsigned short port){
  unsigned int index = 0;
  bool find = false;

  while(index < this->clients.size() && !find){
    if(this->clients[index].ip == ip && this->clients[index].port == port){
      this->clients.erase(this->clients.begin() + index);
      find = true;
    }
    index++;
  }
}

ClientInformation& NetworkServer::addCLient(sf::IpAddress ip, unsigned short port, unsigned int uid){
  ClientInformation client;

  client.ip = ip;
  client.port = port;
  client.uid = uid;
  client.state = State::untested;
  client.nbUpdateMaxNotConfirmed = 8;
  client.nbUpdateNotConfirmed = 0;

  this->clients.push_back(client);
  return this->clients[this->clients.size() - 1];
}

bool NetworkServer::clientActive(ClientInformation &client){
  if(client.nbUpdateNotConfirmed >= client.nbUpdateMaxNotConfirmed){
    client.state = State::inactive;
    return false;
  }
  return true;
}

bool NetworkServer::addCharacterClient(std::string& name, TypeCharacter& type, unsigned int uid){
  Character* character = new Character(name, type);
  character->setUid(uid);
  return this->model->addCharacter(character);
}

void NetworkServer::removeCharacterClient(const sf::IpAddress &adressClient, unsigned short port, const std::string& name){
  std::cout << "deconnection de " << name << std::endl;
  this->model->removeEntitie(name);
}

unsigned int NetworkServer::getId(){
  return NetworkServer::id;
}