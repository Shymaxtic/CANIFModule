/*****************************************************************************
    Semaphore.h

    Created: 18 2019 by shymaxtic

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
#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include <mutex>
#include <condition_variable>
#include <SystemDefine.h>

template<int maxSize=1>
class Semaphore {
    public:
        explicit Semaphore(uint32_t cnt = 0);
        virtual ~Semaphore();
    public:
        int Release(); // indicate a resource is available.
        int Acquire(uint64_t time = 0); // wait for a resource is available.
    private:
        uint32_t                mMaxCnt;
        uint32_t                mCnt;
        std::mutex              mLock;
        std::condition_variable mWait;
};


template<int maxSize>
Semaphore<maxSize>::Semaphore(uint32_t cnt) :
    mMaxCnt(maxSize),
    mCnt(cnt) {
    if (mMaxCnt == 0) {
        throw std::invalid_argument("max count must greater than 0.");
    }
}
template<int maxSize>
Semaphore<maxSize>::~Semaphore() {

}

template<int maxSize>
int Semaphore<maxSize>::Release() {
    std::unique_lock<std::mutex> lcker(mLock); // I take it, you guys should wait for me.

    if (mCnt == 0) {
        mCnt++;
        mWait.notify_all(); //to you guys who need a resoure. Now a resource is available, take it and make something!
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

template<int maxSize>
int Semaphore<maxSize>::Acquire(uint64_t timeus) {

    std::unique_lock<std::mutex> lcker(mLock); // you guys wait for me.

    if (mCnt > 0) {   // I take a resource.
        mCnt--;
        return S_OK;
    }

    else {

        if (timeus == 0) {
            mWait.wait(lcker); // I wait forever.
        }
        else {
            std::cv_status stt = mWait.wait_for(lcker, std::chrono::microseconds(timeus)); // I wait for a while.
            return (stt == std::cv_status::no_timeout) ? S_OK : S_SEM_TIMEOUT;
        }
    }
    return S_OK;
}


#endif // SEMAPHORE_H

/* When using template, all definitions should be put in header file.
 * Or you can instantiate a template instance a bottom of cpp file
 * template class Semaphore<128>;
 */




