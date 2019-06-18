#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

using namespace std;
#include "CANIFModule.h"
#include "Debug.h"

static void ReceiveCallback(ReceiveChannel &rcvCh) {
    std::deque<can_frame> rx = rcvCh.ReadFifo();
    for (std::deque<can_frame>::iterator it = rx.begin();
            it != rx.end(); ++it) {
        can_frame frame = *it;
        DBG_VAR(frame.can_id);
    }
}


int main(int argc, char *argv[]) {
    if (CANService::GetInstance().CreateConnection("vcan0")) {
        CANIFPtr vcan0 = CANService::GetInstance().Device("vcan0");
        if (vcan0 != nullptr) {
            vcan0->GetReceiveChannel()->RegisterReceiveCallback(ReceiveCallback);
            vcan0->Active();
            getchar();
            DBG_MSG("Start transmiting...");
            for (uint8_t i = 0; i < 100; i++) {
                std::deque<can_frame_ptr> frames;
                for (uint8_t j = 0; j < 5; j++) {
                    can_frame_ptr frame(new can_frame);
                    frame->can_id = i;
                    frame->can_dlc = 8;
                    frames.push_back(frame);
                }
                vcan0->GetTransmitChannel()->WriteFifo(frames);
                usleep(100000);
            }
            getchar();
            vcan0->Deactive();
        }
    }
    return 0;
}

