/*****************************************************************************
    Semaphore.cpp

    Created: 18 2019 by quynhpp

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
#include "Semaphore.h"
#include "SystemDefine.h"

Semaphore::Semaphore(uint32_t maxCnt, uint32_t cnt) :
    mMaxCnt(maxCnt),
    mCnt(cnt) {
    if (maxCnt == 0) {
        throw std::invalid_argument("max count must greater than 0.");
    }
}

Semaphore::~Semaphore() {

}

int Semaphore::Release() {
    std::unique_lock<std::mutex> lcker(mLock);
    if (mCnt == 0) {
        mCnt++;
        mWait.notify_all();
    }
    else {
        mCnt++;
        if (mCnt > mMaxCnt) {
            mCnt = mMaxCnt;
            return S_SEM_OVERMAX;
        }
    }
    return S_OK;
}

int Semaphore::Acquire(uint64_t timeus) {
    std::unique_lock<std::mutex> lcker(mLock);
    if (mCnt > 0) {
        mCnt--;
        return S_OK;
    }
    else {
        if (timeus == 0) {
            mWait.wait(lcker);
        }
        else {
            std::cv_status stt = mWait.wait_for(lcker, std::chrono::microseconds(timeus));
            return (stt == std::cv_status::no_timeout) ? S_OK : S_SEM_TIMEOUT;
        }
    }
    return S_OK;
}
