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
#ifndef TRANSMITCHANNEL_H
#define TRANSMITCHANNEL_H
#include "CANIF.h"

class TransmitChannel {
    public:
        TransmitChannel(CANIF &);
        ~TransmitChannel();
        bool Active();
        bool Deactive();
        std::deque<can_frame_ptr>       ReadFifo();
        void                        WriteFifo(const std::deque<can_frame_ptr> &frames);
        template<typename Callable, typename ...Args>
        bool RegisterTransmitCallback(Callable &&callback, Args &&... _args) {
            std::function<void(void)> bindFunc = std::bind(std::forward<Callable>(callback),
                                                           std::ref(*this),
                                                           std::forward<Args>(_args)...);
            mCallback = bindFunc;
            return true;
        }
    private:
        bool                            mStop               = true;
        std::unique_ptr<std::thread>    mTransThread          = nullptr;
        std::mutex                      mTransmitTriggerLock;
        std::deque<can_frame_ptr>           mTxFifo;
        std::mutex                      mFifoLock;
        std::function<void(void)>       mCallback;
        static void TransmitThreadFunc(TransmitChannel &);
        CANIF &mCANIf;
};

#endif // TRANSMITCHANNEL_H
