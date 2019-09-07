/*****************************************************************************
    CANServiceIF.cpp

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
#include "CANServiceIF.h"

CANServiceIF::CANServiceIF() {
    mTrnCh = new CANTransmitChannel(this, &mCANSckIF);
    mRcvCh = new CANReceiveChannel(this, &mCANSckIF);
}

CANServiceIF::~CANServiceIF() {
    delete mTrnCh;
    delete mRcvCh;
}

int CANServiceIF::Connect(const std::string sckNm) {
    return mCANSckIF.Connect(sckNm);
}

int CANServiceIF::Disconnect() {
    return mCANSckIF.Disconnect();
}

int CANServiceIF::StartChannel() {
    mTrnCh->Start();
    mRcvCh->Start();
    return S_OK;
}

int CANServiceIF::StopChannel() {
    mTrnCh->Stop();
    mRcvCh->Stop();
    return S_OK;
}

int CANServiceIF::Send(const can_frame_ptr &frm) {
    return mTrnCh->Write(frm);
}

int CANServiceIF::Receive(const can_frame_ptr &frm) {
    mCallback(frm);
    return S_OK;
}

void CANServiceIF::SetCallback(std::function<void (const can_frame_ptr &)> cb) {
    mCallback = cb;
}
