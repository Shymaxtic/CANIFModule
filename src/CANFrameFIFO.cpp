/*****************************************************************************
    CANFrameFIFO.cpp

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
#include "CANFrameFIFO.h"


CANFrameFIFO::CANFrameFIFO():
    mAvailabeSem(D_MAXIMUM_FRM_FIFO, D_MAXIMUM_FRM_FIFO),
    mUsedsem(D_MAXIMUM_FRM_FIFO, 0) {
}

CANFrameFIFO::~CANFrameFIFO() {

}

int CANFrameFIFO::Push(const can_frame_ptr &frm, uint64_t timeUs) {
    if (mAvailabeSem.Acquire(timeUs) != S_OK) {
        return S_ERR;
    }
    std::lock_guard<std::mutex> lkc(mMux);
    if (mFrames.size() < D_MAXIMUM_FRM_FIFO) {
        mFrames.push_back(frm);
    }
    else {
        return S_ERR;
    }
    mUsedsem.Release();
    return S_OK;
}

int CANFrameFIFO::Pop(can_frame_ptr &frm, uint64_t timeUs) {
    if (mUsedsem.Acquire(timeUs) != S_OK) {
        return S_ERR;
    }
    std::lock_guard<std::mutex> lkc(mMux);
    if (mFrames.empty() == false) {
        frm = mFrames.front();
        mFrames.pop_front();
    }
    else {
        return S_ERR;
    }
    mAvailabeSem.Release();
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
