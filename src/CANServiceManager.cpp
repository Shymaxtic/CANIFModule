/*****************************************************************************
    CANServiceManager.cpp

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
#include "CANServiceManager.h"


std::shared_ptr<CANServiceManager> CANServiceManager::gInstance = nullptr;

CANServiceManager::CANServiceManager() {

}

CANServiceManager::~CANServiceManager() {

}

int CANServiceManager::Connect(const std::string &sckName) {
    CANServiceIFPtr newCAN(new CANServiceIF);
    if (newCAN->Connect(sckName) == S_OK) {
        mConnectedDevs[sckName] = newCAN;
        return S_OK;
    }
    else {
        return S_ERR;
    }
    return S_OK;
}

int CANServiceManager::Disconnect(const std::string &sckName) {
    CANServiceIFPtr canSrv = nullptr;
    try {
        canSrv = mConnectedDevs.at(sckName);
        if (canSrv != nullptr) {
            return canSrv->Disconnect();
        }
        else {
            return S_ERR;
        }
    }
    catch (std::out_of_range e) {
        return S_ERR;
    }
    return S_OK;
}

int CANServiceManager::Active(const std::string &sckName) {
    CANServiceIFPtr canSrv = nullptr;
    try {
        canSrv = mConnectedDevs.at(sckName);
        if (canSrv != nullptr) {
            return canSrv->StartChannel();
        }
        else {
            return S_ERR;
        }
    }
    catch (std::out_of_range e) {
        return S_ERR;
    }
    return S_OK;
}

int CANServiceManager::Deactive(const std::string &sckName) {
    CANServiceIFPtr canSrv = nullptr;
    try {
        canSrv = mConnectedDevs.at(sckName);
        if (canSrv != nullptr) {
            return canSrv->StopChannel();
        }
        else {
            return S_ERR;
        }
    }
    catch (std::out_of_range e) {
        return S_ERR;
    }
    return S_OK;
}

int CANServiceManager::Send(const std::string sckName, const can_frame_ptr &frm) {
    CANServiceIFPtr canSrv = nullptr;
    try {
        canSrv = mConnectedDevs.at(sckName);
        if (canSrv != nullptr) {
            return canSrv->Send(frm);
        }
        else {
            return S_ERR;
        }
    }
    catch (std::out_of_range e) {
        return S_ERR;
    }
    return S_OK;
}
