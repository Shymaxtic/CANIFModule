/*****************************************************************************
    CANFrameFIFO.cpp

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
#include "CANFrameFIFO.h"


CANFrameFIFO::CANFrameFIFO():
    mAvailabeSem(D_MAXIMUM_FRM_FIFO, D_MAXIMUM_FRM_FIFO), // maximum slot availalbe.
    mUsedsem(D_MAXIMUM_FRM_FIFO, 0) {   // maximum slot availalbe
}

CANFrameFIFO::~CANFrameFIFO() {

}

int CANFrameFIFO::Push(const can_frame_ptr &frm, uint64_t timeUs) {

    if (mAvailabeSem.Acquire(timeUs) != S_OK) { // Someone need a slot for new resource, check and wait for a while.
        return S_ERR;   // oops! there is no any slot available.
    }

    std::lock_guard<std::mutex> lkc(mMux); // there is a slot, lock the door! I will do my job for this guy in the warehouse.

    if (mFrames.size() < D_MAXIMUM_FRM_FIFO) {
        mFrames.push_back(frm);
    }
    else {
        return S_ERR; // oops, the warehouse is full!
    }

    mUsedsem.Release(); // a slot has been occuped. indicate to other guys.

    return S_OK;
}

int CANFrameFIFO::Pop(can_frame_ptr &frm, uint64_t timeUs) {

    if (mUsedsem.Acquire(timeUs) != S_OK) { // Someone need a resource from warehouse, check and wait for a while.
        return S_ERR;           // oops! there is no any resource available.
    }

    std::lock_guard<std::mutex> lkc(mMux);  // there is a  slot, lock the door! I will get it for this guy.

    if (mFrames.empty() == false) {
        frm = mFrames.front();
        mFrames.pop_front();
    }

    else {
        return S_ERR; // oops, the warehouse is empty!
    }

    mAvailabeSem.Release(); // I take a resurce, indicate to other guys that they can put at least a resource to ware house.

    return S_OK;
}

int CANFrameFIFO::Clear() {
    std::lock_guard<std::mutex> lkc(mMux);
    while (mFrames.empty() == false) {
        mUsedsem.Acquire();
        mFrames.pop_front();
        mAvailabeSem.Release();
    }
    return S_OK;
}
