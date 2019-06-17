/*****************************************************************************
 * CANService
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
#include "CANService.h"
#include "Debug.h"

std::shared_ptr<CANService> CANService::gInstance = nullptr;

CANService::CANService() {
}

CANService::~CANService() {
}

bool CANService::CreateConnection(const std::__cxx11::string portName) {
    try {
        CANIFPtr newDev(new CANIF(portName));
        mConnectedDevs[portName] = newDev;
    } catch (std::runtime_error e) {
        return false;
    }
    return true;
}

CANIFPtr CANService::Device(const std::__cxx11::string portName) const {
    CANIFPtr ret = nullptr;
    try {
        ret = mConnectedDevs.at(portName);
    } catch (std::out_of_range e) {
        ret = nullptr;
    }
    return ret;
}
