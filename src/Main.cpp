#include "tool/mainFunctions/functionsInitGame.h"
#include "tool/mainFunctions/functionsLaunchGame.h"

int main(){
    int width = 920;
    int height = 680;

    bool isMulti = initIsMulti();
    bool isHost = initIsHost();
    std::string ip = initIp();
    int port = initPort();

    if(!isMulti){
      launchSolo(width, height);
    }else if(isHost){
      launchServer(width, height, port);
    }else{
      launchClient(width, height, ip, port);
    }

    return 0;
}
