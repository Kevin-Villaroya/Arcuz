#include "NetworkClient.h"
#include <iostream>
#include <functional>
#include <SFML/Network/Packet.hpp>
#include "data/NetworkData.h"
#include <experimental/filesystem>
#include "../../viewer/texture/CharacterTexture.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

sf::Mutex mutex;

NetworkClient::NetworkClient(int width, int height, std::string ip, unsigned int port) : Controller(width, height), ip(ip), thread(&NetworkClient::updateCLient, this){
  this->port = port;
  this->connectGame();
  this->threadTerminated = true;
}

void NetworkClient::communicate(sf::Packet &packet){
  this->connectServer();
  this->send(packet);
}

bool NetworkClient::connectServer(){
  if(this->socket.connect(this->ip, this->port) == sf::Socket::Done){
    std::cout << "connection succeed" << std::endl;
    return true;
  }
  std::cout << "connection failed" << std::endl;
  return false;
}

void NetworkClient::send(sf::Packet &packet){
  if(!this->socket.send(packet) == sf::Socket::Status::Done){
    std::cout << "packet send failed" << std::endl;
  }
}

void NetworkClient::connectGame(){
  sf::Packet packet;

  /*Envoie du nom du personnage et de son apparence*/
  packet << (uint32_t)Action::connect;
  packet << this->model->getMainCharacter()->getName();
  packet << (uint32_t)model->getMainCharacter()->getType();

  this->communicate(packet);
  confirmationOfConnection();
}

void NetworkClient::disconnectGame(){
  sf::Packet packet;

  packet << (uint32_t)Action::disconnect;
  packet << this->model->getMainCharacter()->getName();

  this->communicate(packet);
  std::cout << "deconnection du serveur" << std::endl;
}

void NetworkClient::confirmationOfConnection(){
  sf::Packet receiveUid;
  unsigned int uid;

  if(this->socket.receive(receiveUid) == sf::Socket::Done){
    receiveUid >> uid;
  }

  this->model->getMainCharacter()->setUid(uid);
  std::cout << "Mon id est " << uid << std::endl;
}

void NetworkClient::updateCLient(){
  sf::Packet packet;
  this->threadTerminated = false;

  std::cout << "in update" << std::endl;

  if(this->socket.receive(packet) == sf::Socket::Done){
    std::vector<EntityDrawable*> entities;
    EntityDrawable* entity;
    unsigned int size;

    packet >> size;

    for(unsigned int i = 0; i < size; i++){
      entity = createEntity(packet);
      entity->putOut(packet);
      entities.push_back(entity);
      std::cout << "pos x "<< entity->getPosX() << "pos y " << entity->getPosY()<< std::endl;
    }

    mutex.lock();
    this->model->setEntities(entities);
    mutex.unlock();
  }
  this->threadTerminated = true;
}

void NetworkClient::start(){
  while(this->running){
    mutex.lock();
    this->checkEvents();
    this->model->update();
    this->model->render();
    mutex.unlock();
    if(this->threadTerminated){
      this->thread.launch();
    } 
  }
}

void NetworkClient::checkEvents(){
    sf::Event event;
    while (this->window.pollEvent(event)) {

     if (event.type == sf::Event::KeyPressed){ //ANY KEY PRESSED

       if(event.key.shift){ //SHIFT PRESSED
         if(event.key.code == sf::Keyboard::Right){
           this->model->getMainCharacter()->run(Direction::right);
         }else if(event.key.code == sf::Keyboard::Left){
           this->model->getMainCharacter()->run(Direction::left);
         }else if(event.key.code == sf::Keyboard::Up){
           this->model->getMainCharacter()->run(Direction::up);
         }else if(event.key.code == sf::Keyboard::Down){
           this->model->getMainCharacter()->run(Direction::down);
         }
       }

       else if (event.key.code == sf::Keyboard::Escape){ //CASE ELSE
         this->disconnectGame();
         this->running = false;
       }else if(event.key.code == sf::Keyboard::Right){
         this->model->getMainCharacter()->walk(Direction::right);
       }else if(event.key.code == sf::Keyboard::Left){
         this->model->getMainCharacter()->walk(Direction::left);
       }else if(event.key.code == sf::Keyboard::Up){
         this->model->getMainCharacter()->walk(Direction::up);
       }else if(event.key.code == sf::Keyboard::Down){
         this->model->getMainCharacter()->walk(Direction::down);
       }else{
         if(this->model->getMainCharacter()->getSpeed() != 0){
           this->model->getMainCharacter()->stop();
         }
       }
     }else{ // IF NO KEY PRESSED
       this->model->getMainCharacter()->stop();
     }

     if(event.type == sf::Event::Closed){ // IF WINDOWS CLOSE
       this->disconnectGame();
       this->thread.terminate();
       this->closeGame();
     }
   }
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