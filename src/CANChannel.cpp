/*****************************************************************************
    CANChannel.cpp

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
#include "CANChannel.h"
CANChannel::CANChannel(CANServiceIF *serviceIF, CANSocketIF *canIF) :
    mCANSrvIF(serviceIF),
    mCANSckIF(canIF) {
    if (mCANSckIF == nullptr || mCANSckIF == nullptr) {
        throw std::invalid_argument("nullptr is not permitted.");
    }
}

CANChannel::~CANChannel() {

}

int CANChannel::Write(const can_frame_ptr &frm) {
    return mFIFO.Push(frm);
}

int CANChannel::Read(can_frame_ptr &frm) {
    return mFIFO.Pop(frm, 1000);
}
