#include "NetworkClient.h"
#include <iostream>

NetworkClient::NetworkClient(int width, int height, std::string ip, unsigned int port) : Controller(width, height), ip(ip){
  this->port = port;
}

void NetworkClient::communicate(sf::Packet &packet){
  this->connect();
  this->send(packet);
}

bool NetworkClient::connect(){
  if(this->socket.connect(this->ip, this->port) == sf::Socket::Done){
    std::cout << "connection succeed" << std::endl;
    return true;
  }
  std::cout << "connection failed" << std::endl;
  return false;
}

void NetworkClient::send(sf::Packet &packet){
  if(this->socket.send(packet) == sf::Socket::Status::Done){
    std::cout << "packet send succeed" << std::endl;
  }else{
    std::cout << "packet send failed" << std::endl;
  }
}
