#include "NetworkData.h"

NetworkData::NetworkData(){}

NetworkData::NetworkData(const Action &action, const std::string &data){
  this->action = action;
  this->data = data;
}
