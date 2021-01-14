#include "NetworkServer.h"
#include <iostream>
#include <vector>
#include <typeinfo>
#include <string.h>
#include <../../model/entities/EntityDrawable.h>

NetworkServer::NetworkServer(int width, int height, unsigned int port) : Controller(width, height){
    this->port = port;
    this->listener.listen(this->port);
    this->selector.add(this->listener);
}

void NetworkServer::startServer(){
  while (true){
    if (this->selector.wait()){
      if (this->selector.isReady(listener)){
        sf::TcpSocket* client = new sf::TcpSocket;
        if (listener.accept(*client) == sf::Socket::Done){
          clients.push_back(client);
          this->selector.add(*client);
        }else{
          delete client;
        }
      }else {
        for (unsigned int i = 0; i < this->clients.size(); i++){
          sf::TcpSocket& client = *this->clients[i];
          if (this->selector.isReady(client)){
            sf::Packet packet;
            if (client.receive(packet) == sf::Socket::Done){
              this->processingRequest(client, packet);
            }
          }
        }
      }
    }
  }
}

void NetworkServer::start(){
  while(this->running){
    this->checkEvents();
    this->model->update();
    this->model->render();
    this->updateAllCLient();
  }
}

void NetworkServer::processingRequest(sf::TcpSocket &socket, sf::Packet &packet){
  uint32_t action_int;
  Action action;
  std::string name;

  packet >> action_int;
  action = (Action)action_int;

  if(action == Action::connect){
    this->connectClient(socket, packet);
  }else if (action == Action::disconnect){
    packet >> name;
    this->removeCharacterClient(socket, name);
  }else if(action == Action::walk_right){
    this->clientWalk(socket, Direction::right);
  }
}

void  NetworkServer::updateAllCLient(){
  sf::Packet packet;
  std::vector<EntityDrawable*> entities = this->model->getEntities();
  entities.push_back(this->model->getMainCharacter());
  unsigned int size = (unsigned int) entities.size();
  packet << size;

  for(unsigned int i = 0; i < size; i++){
    entities[i]->putIn(packet);
  }

  for (unsigned int i = 0; i < this->clients.size(); i++){
    sf::TcpSocket& client = *this->clients[i];
    if (this->selector.isReady(client)){
      client.send(packet);
    }
  }
}

void NetworkServer::connectClient(sf::TcpSocket &socket, sf::Packet& packet){
  std::string name;
  uint32_t type_int;
  TypeCharacter type;
  unsigned int uid;

  packet >> name;
  packet >> type_int;
  type = (TypeCharacter)type_int;
  uid = this->model->quantityOfEntities() + 1;

  std::cout << "le joueur " << name << " essaie de se connecter, son uid est " << uid << std::endl;

  this->addCharacterClient(name, type);

  sf::Packet packetSend;
  packetSend << "Votre numero uid est" << uid;
  socket.send(packetSend);
}

void NetworkServer::addCharacterClient(std::string& name, TypeCharacter& type){
  Character* character = new Character(name, type);
  this->model->addCharacter(character);
}

void NetworkServer::removeCharacterClient(sf::TcpSocket &socket, const std::string& name){
  this->model->removeEntitie(name);

  sf::Packet packetSend;
  packetSend << "Votre déconnection est confirmer";
  socket.send(packetSend);
}

void NetworkServer::clientWalk(sf::TcpSocket &socket, Direction direction){
  //Choose the good character and move it
}
