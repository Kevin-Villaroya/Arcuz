#include "tool/mainFunctions/functionsInitGame.h"
#include "tool/mainFunctions/functionsLaunchGame.h"
#include <string.h>

int main(int argc, char* argv[]){
    int width = 920;
    int height = 680;

    bool isMulti = initIsMulti();
    bool isHost = initIsHost();
    std::string ip = initIp();
    int port = initPort();

    if(argc == 2){
      if(strcmp(argv[1], "-h") == 0){
        isHost = true;
      }else if(strcmp(argv[1], "-c") == 0){
        isHost = false;
      }
    }

    if(!isMulti){
      launchSolo(width, height);
    }else if(isHost){
      launchServer(width, height, port);
    }else{
      launchClient(width, height, ip, port);
    }

    return 0;
}
