/*****************************************************************************
    CANServiceIF.h

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
#ifndef CANSERVICEIF_H
#define CANSERVICEIF_H

#include "CANTransmitChannel.h"
#include "CANReceiveChannel.h"
#include "CANSocketIF.h"
#include <functional>
#include "SystemDefine.h"

class CANServiceIF {
    public:
        CANServiceIF();
        UT_VIRTUAL ~CANServiceIF();
    public:
        int Connect(const std::string sckNm);
        int Disconnect();
        int StartChannel();
        int StopChannel();
        int Send(const can_frame_ptr &frm);
        UT_VIRTUAL int Receive(const can_frame_ptr &frm);
        void SetCallback(std::function<void(const can_frame_ptr &frm)> cb);
    private:
        CANTransmitChannel  *mTrnCh;
        CANReceiveChannel   *mRcvCh;
        CANSocketIF         mCANSckIF;
        std::function<void(const can_frame_ptr &frm)>   mCallback;
};

typedef std::shared_ptr<CANServiceIF> CANServiceIFPtr;

#endif // CANSERVICEIF_H
