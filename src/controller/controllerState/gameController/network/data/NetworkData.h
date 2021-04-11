#ifndef __GAME_PACKET_H__
#define __GAME_PACKET_H__

enum Action{
  connect, /*When a client ask a connection*/
  disconnect, /*When a client ask a disconnection*/
  update, /*When a client is sending is situation*/
  update_map,
  confirm_update, /*When a client confirm to be updated*/
  confirm_disconnect /*When a client is disconnected*/
};

#endif
