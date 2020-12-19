#include "NetworkServer.h"
#include <iostream>
#include <vector>
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
          std::cout << "client connecté" << std::endl;
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
  const NetworkData* data = (NetworkData*)packet.getData();
  if(data->action == Action::connect){
    this->connectClient(socket, *data);
  }else if(data->action == Action::walk_right){
    this->clientWalk(socket, Direction::right);
  }
}

void  NetworkServer::updateAllCLient(){
  sf::Packet packet;
  std::vector<EntityDrawable> entities = this->model->getEntities();
  entities.push_back(this->model->getMainCharacter());
  size_t size = entities.size();
  packet << size;

  for(unsigned int i = 0; i < size; i++){
    packet << entities[i];
  }

  for (unsigned int i = 0; i < this->clients.size(); i++){
    sf::TcpSocket& client = *this->clients[i];
    if (this->selector.isReady(client)){
      std::cout << "send entities to clients" << std::endl;
      std::cout << "number of entities " << entities.size() << std::endl;
      client.send(packet);
    }
  }
}

void NetworkServer::connectClient(sf::TcpSocket &socket, const NetworkData &data){
  this->addCharacterClient(data.data);
}

void NetworkServer::addCharacterClient(std::string name){
  Character character = Character(name);
  this->model->addCharacter(character);
}

void NetworkServer::clientWalk(sf::TcpSocket &socket, Direction direction){
  //Choose the good character and move it
}
