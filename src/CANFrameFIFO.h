/*****************************************************************************
    CANFrameFIFO.h

    Created: 01 2019 by shymaxtic

    Copyright 2019 shymaxtic. All rights reserved.

    This file may be distributed under the terms of GNU Public License version
    3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
    license should have been included with this file, or the project in which
    this file belongs to. You may also find the details of GPL v3 at:
    http://www.gnu.org/licenses/gpl-3.0.txt

    If you have any questions regarding the use of this file, feel free to
    contact the author of this file, or the owner of the project in which
    this file belongs to.
 *****************************************************************************/
#ifndef CANFRAMEFIFO_H
#define CANFRAMEFIFO_H
#include <deque>
#include "SystemDefine.h"
#include "Semaphore.h"

#define D_MAXIMUM_FRM_FIFO      128


class CANFrameFIFO { // I am a warehosue for you guys.

    public:
        CANFrameFIFO();
        ~CANFrameFIFO();

    public:
        int Push(const can_frame_ptr &frm, uint64_t timeUs = 0); // some one push a resource to me.
        int Pop(can_frame_ptr &frms, uint64_t timeUs = 0);      // some one get a resource from me to do something.
        int Clear();    // time for sale, clear the inventory.

    private:
        std::deque<can_frame_ptr>           mFrames;
        Semaphore<D_MAXIMUM_FRM_FIFO>       mAvailabeSem;
        Semaphore<D_MAXIMUM_FRM_FIFO>       mUsedsem;
        std::mutex                          mMux;

};
#endif // CANFRAMEFIFO_H
