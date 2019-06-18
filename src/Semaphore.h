/*****************************************************************************
 * Semaphore.h
 *
 * Created: 18 2019 by shymaxtic
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
#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include <mutex>
#include <condition_variable>

class Semaphore {
    public:
        explicit Semaphore(uint32_t maxCnt = 1);
        ~Semaphore();
    public:
        void Up();
        void Down();
    private:
        uint32_t                mMaxCnt;
        uint32_t                mCnt = 0;
        std::mutex              mLock;
        std::condition_variable mWait;
};

#endif // SEMAPHORE_H
