/*****************************************************************************
    CANReceiveChannel.cpp

    Created: 01 2019 by quynhpp

    Copyright 2019 quynhpp. All rights reserved.

    This file may be distributed under the terms of GNU Public License version
    3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
    license should have been included with this file, or the project in which
    this file belongs to. You may also find the details of GPL v3 at:
    http://www.gnu.org/licenses/gpl-3.0.txt

    If you have any questions regarding the use of this file, feel free to
    contact the author of this file, or the owner of the project in which
    this file belongs to.
 *****************************************************************************/
#include "CANReceiveChannel.h"
#include "CANSocketIF.h"
#include "CANServiceIF.h"
#include "Debug.h"

CANReceiveChannel::CANReceiveChannel(CANServiceIF *serviceIF, CANSocketIF *canIF) :
    CANChannel(serviceIF, canIF) {

}

int CANReceiveChannel::Start() {
    mIsStop = false;
    mReceiveThread = std::thread(&CANReceiveChannel::ReceiveFunc, this);
    return S_OK;
}

int CANReceiveChannel::Stop() {
    mIsStop = true;
    mReceiveThread.join();
    mFIFO.Clear();
    return S_OK;
}

void CANReceiveChannel::ReceiveFunc() {
    while (mIsStop == false) {
        if (mCANSckIF->AcquireData(100) == S_OK) {
            can_frame_ptr rcvFrm(new can_frame);
            if (mCANSckIF->ReadFrame(rcvFrm) == S_OK) {
                //                Write(rcvFrm);
                mCANSrvIF->Receive(rcvFrm);
            }
        }
    }
}
