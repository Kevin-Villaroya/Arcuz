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

    if(line.substr(pos + 1, line.length()) == "true"){
      return true;
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

    if(line.substr(0, pos - 1) == "server_ip"){
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

    if(line.substr(0, pos - 1) == "server_port"){
      return std::stoi(line.substr(pos + 1, line.length()));
    }
  }
  return 55250;
}
