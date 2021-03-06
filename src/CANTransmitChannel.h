/*****************************************************************************
    CANTransmitChannel.h

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
#ifndef CANTRANSMITCHANNEL_H
#define CANTRANSMITCHANNEL_H

#include "CANChannel.h"
#include <thread>


class CANTransmitChannel : public CANChannel { // I am a guy who is responesible for take resouce and do the job.
    public:
        CANTransmitChannel(CANServiceIF *srvIF, CANSocketIF *canIF);
    public:
        int Start() override;
        int Stop() override;
    private:
        std::thread         mTransmitThread;
        void                TransmitFunc();
};

#endif // CANTRANSMITCHANNEL_H
