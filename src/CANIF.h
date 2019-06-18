/*****************************************************************************
 * CANIF
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
#ifndef CANIF_H
#define CANIF_H
#include <thread>
#include <memory>
#include "CANSocketIF.h"
#include <condition_variable>
#include <mutex>
#include <deque>
#include <linux/can.h>
#include <functional>

class ReceiveChannel;
class TransmitChannel;
typedef std::shared_ptr<ReceiveChannel>  ReceiveChannelPtr;
typedef std::shared_ptr<TransmitChannel>  TransmitChannelPtr;
class CANIF {
    public:
        CANIF(const std::string portName);
        ~CANIF();
    public:
        bool    Active();
        bool    Deactive();
        const ReceiveChannelPtr &GetReceiveChannel();
        const TransmitChannelPtr &GetTransmitChannel();

    private:
        CANSocketIF                     mSocketIF;
        ReceiveChannelPtr               mRcvChannel;
        TransmitChannelPtr              mTransChannel;
        friend class ReceiveChannel;
        friend class TransmitChannel;
};

#endif // CANIF_H
