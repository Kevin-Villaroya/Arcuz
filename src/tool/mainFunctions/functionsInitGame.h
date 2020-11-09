#include <string>
#include <fstream>
#include <iostream>

bool initIsHost(){
  std::string line;
  std::ifstream myfile;
  std::string delimiter = ":";
  size_t pos = 0;

  myfile.open("config.ini");

  while(getline(myfile, line)){
    pos = line.find(delimiter);

    if(line.substr(0, pos) == "host"){
      if(line.substr(pos + 1, line.length()) == "true"){
        return true;
      }else{
        return false;
      }
    }
  }
  return false;
}

std::string initIp(){
  std::string line;
  std::ifstream myfile;
  std::string delimiter = ":";
  size_t pos = 0;

  myfile.open("config.ini");

  while(getline(myfile, line)){
    pos = line.find(delimiter);

    if(line.substr(0, pos) == "server_ip"){
      return line.substr(pos + 1, line.length());
    }
  }
  return "127.0.0.1";
}

int initPort(){
  std::string line;
  std::ifstream myfile;
  std::string delimiter = ":";
  size_t pos = 0;

  myfile.open("config.ini");

  while(getline(myfile, line)){
    pos = line.find(delimiter);

    if(line.substr(0, pos) == "server_port"){
      return std::stoi(line.substr(pos + 1, line.length()));
    }
  }
  return 55250;
}

bool initIsMulti(){
  std::string line;
  std::ifstream myfile;
  std::string delimiter = ":";
  size_t pos = 0;

  myfile.open("config.ini");

  while(getline(myfile, line)){
    pos = line.find(delimiter);

    if(line.substr(0, pos) == "online"){
      if(line.substr(pos + 1, line.length()) == "true"){
        return true;
      }else{
        return false;
      }
    }
  }
  return false;
}
