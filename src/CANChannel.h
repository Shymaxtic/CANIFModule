/*****************************************************************************
    CANChannel.h

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
#ifndef CANCHANNEL_H
#define CANCHANNEL_H

#include "CANFrameFIFO.h"

class CANSocketIF;
class CANServiceIF;

class CANChannel {
    public:
        CANChannel(CANServiceIF *serviceIF, CANSocketIF *canIF);
        virtual ~CANChannel();
    public:
        virtual int Start() = 0;
        virtual int Stop() = 0;
    public:
        int Write(const can_frame_ptr &frm);
        int Read(can_frame_ptr &frm);
    protected:
        bool            mIsStop = false;
        CANFrameFIFO    mFIFO;
        CANServiceIF    *mCANSrvIF;
        CANSocketIF     *mCANSckIF;

};



#endif // CANCHANNEL_H

