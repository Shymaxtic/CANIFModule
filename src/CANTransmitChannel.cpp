/*****************************************************************************
    CANTransmitChannel.cpp

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
#include "CANTransmitChannel.h"
#include "CANSocketIF.h"
#include "Debug.h"

CANTransmitChannel::CANTransmitChannel(CANServiceIF *srvIF, CANSocketIF *canIF) :
    CANChannel(srvIF, canIF) {

}

int CANTransmitChannel::Start() {
    mIsStop = false;
    mTransmitThread = std::thread(&CANTransmitChannel::TransmitFunc, this);
    return S_OK;
}

int CANTransmitChannel::Stop() {
    mIsStop = true;
    mTransmitThread.join();
    mFIFO.Clear();
    return S_OK;
}

void CANTransmitChannel::TransmitFunc() {
    while (mIsStop == false) {
        can_frame_ptr txFr;
        if (mFIFO.Pop(txFr, 1000) == S_OK) {
            mCANSckIF->SendFrame(txFr);
            //            DBG_MSG(txFr->can_id);
        }
    }
}
