#ifndef __GAME_PACKET_H__
#define __GAME_PACKET_H__

#include <string>

enum Action{
  connect,
  walk_right,
  walk_left,
  walk_up,
  walk_down
};

class NetworkData{
public:
  Action action;
  std::string data;

  NetworkData();
  NetworkData(const Action &action, const std::string &data);
};

#endif
