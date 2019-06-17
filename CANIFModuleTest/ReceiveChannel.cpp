/*****************************************************************************
 * ReceiveChannel
 *
 * Created: 17 2019 by shymaxtic
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
#include "ReceiveChannel.h"
#include "Debug.h"

ReceiveChannel::ReceiveChannel(CANIF &canIf) :
    mCANIf(canIf) {

}

ReceiveChannel::~ReceiveChannel() {

}

bool ReceiveChannel::Active() {
    if (mRcvThread == nullptr) {
        mStop = false;
        mRcvThread = std::unique_ptr<std::thread>(new std::thread(ReceiveChannel::ReceiveThreadFunc, std::ref(*this)));
        if (mRcvThread == nullptr) {
            return false;
        }
    }
    return true;
}

bool ReceiveChannel::Deactive() {
    if (mRcvThread != nullptr) {
        do {
            std::lock_guard<std::mutex> lock(mReceiveTriggerLock);
            mStop = true;
        } while (0);
        mRcvThread->join();
        mRcvThread = nullptr;
        mRxFifo.clear();
    }
    return true;
}

std::deque<can_frame> ReceiveChannel::ReadFifo() {
    std::lock_guard<std::mutex> lker(mFifoLock);
    std::deque<can_frame> ret = mRxFifo;
    mRxFifo.clear();
    return ret;
}

void ReceiveChannel::WriteFifo(const std::deque<can_frame> &frames) {
    std::lock_guard<std::mutex> lker(mFifoLock);
    for (std::deque<can_frame>::const_iterator it = frames.begin();
            it != frames.end(); ++it) {
        mRxFifo.push_back(*it);
    }
}

void ReceiveChannel::WriteFifo(const can_frame &frame) {
    std::lock_guard<std::mutex> lker(mFifoLock);
    mRxFifo.push_back(frame);
}

void ReceiveChannel::ReceiveThreadFunc(ReceiveChannel &rcvCh) {
    while (rcvCh.mStop == false) {
        if (rcvCh.mCANIf.mSocketIF.AcquireData(100) == true) {
            can_frame rcvFrm;
            if (rcvCh.mCANIf.mSocketIF.ReadFrame(rcvFrm) > 0) {
                rcvCh.WriteFifo(rcvFrm);
                rcvCh.mCallback();
            }
        }
    }
    DBG_MSG("Stop receive thread");
}
