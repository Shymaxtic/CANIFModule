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

static void ReceiveCallback(const can_frame_ptr &frm) {
    std::cerr << std::hex << frm->can_id << std::endl;
}


int main(int argc, char *argv[]) {
    int ret = CANServiceManager::GetInstance().Connect("vcan0");
    if (ret != S_OK) goto __finish;

    ret = CANServiceManager::GetInstance().RegisterReceiveCallback("vcan0", ReceiveCallback);
    if (ret != S_OK) goto __finish;

    ret = CANServiceManager::GetInstance().Active("vcan0");
    if (ret != S_OK) goto __finish;

    getchar();
    DBG_MSG("Start transmiting...");
    for (uint8_t i = 0; i < 128; i++) {
        for (uint8_t j = 0; j < 5; j++) {
            can_frame_ptr frame(new can_frame);
            frame->can_id = i;
            frame->can_dlc = 8;
            ret = CANServiceManager::GetInstance().Send("vcan0", frame);
            if (ret != S_OK) {
                ERR_MSG(ret);
            }
        }
        usleep(1000);
    }
    getchar();
    CANServiceManager::GetInstance().Deactive("vcan0");
    CANServiceManager::GetInstance().Disconnect("vcan0");

__finish:
    ERR_MSG(ret);
    return 0;
}

