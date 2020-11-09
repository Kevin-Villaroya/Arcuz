#include "NetworkServer.h"
#include <iostream>
#include "data/NetworkData.h"

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

void NetworkServer::processingRequest(sf::TcpSocket &socket, sf::Packet &packet){
  const NetworkData* data = (NetworkData*)packet.getData();
  if(data->action == Action::connect){
    std::cout << socket.getRemoteAddress().toString() <<" se connecte au serveur" << std::endl;
  }
}
