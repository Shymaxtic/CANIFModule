/*****************************************************************************
 * TransmitChannel
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
#include "TransmitChannel.h"
#include "Debug.h"

TransmitChannel::TransmitChannel(CANIF &canIf) :
    mCANIf(canIf) {

}

TransmitChannel::~TransmitChannel() {

}

bool TransmitChannel::Active() {
    if (mTransThread == nullptr) {
        mStop = false;
        mTransThread = std::unique_ptr<std::thread>(new std::thread(TransmitChannel::TransmitThreadFunc, std::ref(*this)));
        if (mTransThread == nullptr) {
            return false;
        }
    }
    return true;
}

bool TransmitChannel::Deactive() {
    if (mTransThread != nullptr) {
        do {
            std::lock_guard<std::mutex> lock(mTransmitTriggerLock);
            mStop = true;
            mTxSem.Up();
        } while (0);
        mTransThread->join();
        mTransThread = nullptr;
        mTxFifo.clear();
    }
    return true;
}

std::deque<can_frame_ptr> TransmitChannel::ReadFifo() {
    mTxSem.Down();
    std::lock_guard<std::mutex> lker(mFifoLock);
    std::deque<can_frame_ptr> ret = mTxFifo;
    mTxFifo.clear();
    return ret;
}

void TransmitChannel::WriteFifo(const std::deque<can_frame_ptr> &frames) {
    std::lock_guard<std::mutex> lker(mFifoLock);
    for (std::deque<can_frame_ptr>::const_iterator it = frames.begin();
            it != frames.end(); ++it) {
        mTxFifo.push_back(*it);
    }
    mTxSem.Up();
}

void TransmitChannel::TransmitThreadFunc(TransmitChannel &transmitCh) {
    while (transmitCh.mStop == false) {
        std::deque<can_frame_ptr> txFrames = transmitCh.ReadFifo();
        for (std::deque<can_frame_ptr>::iterator it = txFrames.begin();
                it != txFrames.end(); ++it) {
            transmitCh.mCANIf.mSocketIF.SendFrame(*it);
        }
    }
    DBG_MSG("Stop transmit channel");
}
