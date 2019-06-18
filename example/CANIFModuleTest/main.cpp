/*****************************************************************************
 * %{Cpp:License:FileName}
 *
 * Created: 18 2019 by shymaxtic
 *
 * Copyright 2019 shymaxtic. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/
#include <iostream>
#include "CANIFModule.h"
#include "Debug.h"
#include <unistd.h>

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
