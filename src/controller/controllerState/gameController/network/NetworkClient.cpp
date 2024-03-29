#include "NetworkClient.h"
#include <iostream>
#include <functional>
#include <SFML/Network/Packet.hpp>
#include <experimental/filesystem>
#include "../../viewer/texture/CharacterTexture.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

sf::Mutex mutex;

NetworkClient::NetworkClient(int width, int height, std::string ip, unsigned short portHost) : GameController(width, height), ip(ip), thread(&NetworkClient::updateCLient, this){
  this->portHost = portHost;
  this->port = sf::Socket::AnyPort;
  this->connectionSucceed = false;
}

NetworkClient::NetworkClient(sf::RenderWindow* window) : GameController(window), thread(&NetworkClient::updateCLient, this){
  this->portHost = 0;
  this->ip = sf::IpAddress();
  this->port = sf::Socket::AnyPort;
  this->connectionSucceed = false;
}

void NetworkClient::setNetwork(){
  if(this->socket.bind(this->port) != sf::Socket::Done){
    std::cout << "Link error" << std::endl;
  }else{
    this->selector.add(this->socket);
    this->connectionSucceed = this->connectGame();

    if(this->connectionSucceed == false){
      this->numberOfConnectionAttempts++;
    }

    this->threadTerminated = true;
  }
}

void NetworkClient::start(){
  if(this->connectionSucceed){
    while(this->running){
      
      this->checkEvents();
      this->model->update();
      this->model->render();
      this->updateServer();
      
      if(this->threadTerminated){
        this->thread.launch();
      }else{
        this->WhenNoUpdateReceived();
      }
    }
    this->disconnectGame();
  }else if(this->numberOfConnectionAttempts < 3){
    this->setNetwork();
    this->start();
  }else{
    this->nextIdScreen = 4;
  }
}

void NetworkClient::checkEvents(){
  GameController::checkEvents();
}

void NetworkClient::needToStart(std::vector<void*> parameters){
  std::string nameCharacter = *(std::string*)(parameters[0]);
  std::string type = *(std::string*)(parameters[1]);

  unsigned short port = *(unsigned short*)(parameters[2]);
  sf::IpAddress ip = *(sf::IpAddress*)(parameters[3]);

  this->portHost = port;
  this->ip = ip;

  std::cout << "Client ready" << std::endl;
  std::cout << "Server Location: ip: " << ip.toString() << ", port: "<< port <<std::endl;

  this->model->setNameCharacter(nameCharacter);
  this->model->getMainCharacter()->setType(type);
  this->numberOfConnectionAttempts = 0;
}

void NetworkClient::send(sf::Packet &packet){
  if(!this->socket.send(packet, this->ip, this->portHost) == sf::Socket::Status::Done){
    std::cout << "packet send failed" << std::endl;
  }
}

sf::Socket::Status NetworkClient::receive(sf::Packet &packet){
  sf::IpAddress ip;
  unsigned short port;
  if (this->selector.wait(sf::seconds(4))){
    if (selector.isReady(socket)){
      return socket.receive(packet, ip, port);
    }
  }

  return sf::Socket::Error;
}

bool NetworkClient::connectGame(){
  sf::Packet packet;

  /*Envoie du nom du personnage et de son apparence*/
  packet << (uint32_t)Action::connect;
  packet << this->model->getMainCharacter()->getName();
  packet << (uint32_t)model->getMainCharacter()->getType();

  std::cout << "Try to connect to the server attempt: " << this->numberOfConnectionAttempts << std::endl;

  this->send(packet);
  return confirmationOfConnection();
}

void NetworkClient::disconnectGame(){
  sf::Packet packet;
  sf::UdpSocket socketTemp;

  packet << (uint32_t)Action::disconnect;
  packet << this->model->getMainCharacter()->getName();
  this->send(packet);
  this->thread.terminate();
  std::cout << "server disconnection" << std::endl;
}

bool NetworkClient::confirmationOfConnection(){
  sf::Packet receiveUid;
  uint32_t info;
  int uid;

  if(this->receive(receiveUid) == sf::Socket::Done){
    receiveUid >> info;
  }else{
    return false;
  }

  if((Action)info == Action::confirm_disconnect){
    std::cout << "Receiving a connection rejection" << std::endl;
    return false;
  }else{
    uid = (int)info;
    this->model->getMainCharacter()->setUid(uid);
    std::cout << "My id is " << uid << std::endl;

    this->receiveMap();
    return true;
  }
}

void NetworkClient::confirmUpdate(){
  sf::Packet packet;
  uint32_t action = Action::confirm_update;
  int uid = this->model->getMainCharacter()->getUid();

  packet << action;
  packet << uid;
  this->send(packet);
}

void NetworkClient::WhenNoUpdateReceived(){
  for(unsigned int i = 0; i < this->model->getEntities().size(); i++){
    this->model->getEntities()[i]->noUpdate();
  }
}

void NetworkClient::receiveMap(){
  sf::Packet packet;
  uint32_t info;

  if(this->receive(packet) == sf::Socket::Done){
    packet >> info;
  }else{
    std::cout << "Packet received for map corrupted" << std::endl;
  }

  if((Action)info == Action::update_map){
    this->model->getMap().putOut(packet);
    this->model->setSpawnPlayers();
  }else{
    std::cout << "Packet received for map corrupted" << std::endl;
  }
}

void NetworkClient::updateCLient(){
  sf::Packet packet;
  int uid;
  this->threadTerminated = false;

  if(this->receive(packet) == sf::Socket::Done){
    EntityDrawable* entity;
    unsigned int size;
    int typeEntity;

    packet >> size;
    
    for(unsigned int i = 0; i < size; i++){
      packet >> uid;
      
      if(!this->model->existEntity(uid)){ 
        entity = createEntity(packet);
        entity->putOut(packet);
        this->model->addEntity(entity);
        entity->setUid(uid);
      }else{
        packet >> typeEntity;
        this->model->getEntity(uid)->putOut(packet);
      }
    }
  }

  this->confirmUpdate();
  this->threadTerminated = true;
}

void NetworkClient::updateServer(){
  sf::Packet packet;

  packet << (uint32_t)Action::update;
  packet << this->model->getMainCharacter()->getUid();

  this->model->getMainCharacter()->putIn(packet);

  this->send(packet);
}

EntityDrawable* NetworkClient::createEntity(sf::Packet& packet){
  int typeEntity;
  packet >> typeEntity;

  if((TypeEntity)typeEntity == TypeEntity::character){
    return new Character();
  }else{
    return new EntityDrawable();
  }
}

unsigned int NetworkClient::getId(){
  return NetworkClient::id;
}