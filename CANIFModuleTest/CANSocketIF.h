/*****************************************************************************
 * CANSocketIF
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
#ifndef CANSOCKETIF_H
#define CANSOCKETIF_H
#include <string>
#include <linux/can.h>
#include <memory>

typedef std::shared_ptr<can_frame>  can_frame_ptr;

class CANSocketIF {
    public:
        CANSocketIF();
        ~CANSocketIF();
        bool   Connect(const std::string portName);
        bool   Disconnect();
        bool   SendFrame(const can_frame_ptr &frame);
        int    ReadFrame(can_frame &frame, uint64_t *sec = nullptr, uint64_t *usec = nullptr);
        bool   AcquireData(int timeout) const;
        int    SocketFD() const;
    private:
        int                     mSocketFd;
        std::string             mPortName;
        struct sockaddr_can     mCANAddr;
};

#endif // CANSOCKETIF_H
