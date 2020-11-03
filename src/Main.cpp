#include "model/Model.h"
#include "controller/Controller.h"
#include "controller/network/Network.h"

int main(){
    Network controller(920,620);
    controller.start();
    return 0;
}
