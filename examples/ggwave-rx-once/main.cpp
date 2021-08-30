#include "ggwave/ggwave.h"

#include "ggwave-common.h"
#include "ggwave-common-sdl2.h"

#include <SDL.h>

#include <cstdio>
#include <thread>

int main(){
   if (GGWave_init(0, 0) == false) {
        fprintf(stderr, "Failed to initialize GGWave\n");
        return -1;
    }

    bool bListen = true;
    while(bListen){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        GGWave_mainLoop();
        GGWave::TxRxData rxData;
        auto rxDataLength = GGWave_instance()->takeRxData(rxData);
        if(rxDataLength>0){
            fprintf(stdout, "%s\n", rxData.data());
            bListen = false;
        }
    }

    GGWave_deinit();

    return 0;
 
}
