#ifndef __CLIENT_INFORMATION_H__
#define __CLIENT_INFORMATION_H__

#include <SFML/Network.hpp>

enum State{
    active,
    inactive,
    untested
};

struct ClientInformation{
    sf::IpAddress ip;
    unsigned short port;
    int uid;
    int nbUpdateNotConfirmed;
    int nbUpdateMaxNotConfirmed;
    State state;
};

#endif