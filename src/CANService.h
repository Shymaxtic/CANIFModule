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
#ifndef CANSERIVCE_H
#define CANSERIVCE_H

#include "CANIF.h"
#include <memory>
#include <unordered_map>

typedef  std::shared_ptr<CANIF>     CANIFPtr;


class  CANService {
    private:
        CANService();
    public:
        ~CANService();
        bool CreateConnection(const std::string portName);
        CANIFPtr Device(const std::string portName) const;
        static CANService &GetInstance() {
            if (gInstance == nullptr) {
                gInstance = std::shared_ptr<CANService>(new CANService());
            }
            return *gInstance;
        }
    private:
        static std::shared_ptr<CANService> gInstance;
        std::unordered_map<std::string, CANIFPtr> mConnectedDevs;
};

#endif // CANSERIVCE_H
