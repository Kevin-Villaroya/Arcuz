#include "Network.h"
#include <fstream>
#include <iostream>

Network::Network(unsigned int width, unsigned int height) : Controller(width, height), ip(initIp()), port(initPort()) {
  this->setUpConnection();
}

void Network::setUpConnection(){
}

/**   Function not in class Network   */

sf::IpAddress initIp(){
  std::ifstream file("config.ini");
  std::string line;
  std::string delimiter = ":";
  sf::IpAddress address;

  while (std::getline(file, line)){
    if(line.substr(0, line.find(delimiter)) == "server_ip"){
      address = sf::IpAddress(line.substr(line.find(delimiter) + 1, line.size()));
    }
  }
  return address;
}

unsigned int initPort(){
  std::ifstream file("config.ini");
  std::string line;
  std::string delimiter = ":";
  unsigned int port;

  while (std::getline(file, line)){
    if(line.substr(0, line.find(delimiter)) == "server_port"){
      port = std::stoi(line.substr(line.find(delimiter) + 1, line.size()));
    }
  }
  return port;
}
