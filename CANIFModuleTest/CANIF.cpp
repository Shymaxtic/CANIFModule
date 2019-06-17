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
#include "CANIF.h"
#include "Debug.h"
#include "ReceiveChannel.h"
#include "TransmitChannel.h"

CANIF::CANIF(const std::string portName)  {
    if (mSocketIF.Connect(portName) == false) {
        throw std::runtime_error("Cannot create connection to: " + portName);
    }
    mRcvChannel = ReceiveChannelPtr(new ReceiveChannel(*this));
    mTransChannel = TransmitChannelPtr(new TransmitChannel(*this));
}

CANIF::~CANIF() {
    mSocketIF.Disconnect();
}

bool CANIF::Active() {
    mRcvChannel->Active();
    mTransChannel->Active();
    return true;
}

bool CANIF::Deactive() {
    mRcvChannel->Deactive();
    mTransChannel->Deactive();
    return true;
}

const ReceiveChannelPtr &CANIF::GetReceiveChannel() {
    return mRcvChannel;
}

const TransmitChannelPtr &CANIF::GetTransmitChannel() {
    return mTransChannel;
}
