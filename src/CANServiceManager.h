/*****************************************************************************
    CANServiceManager.h

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
#ifndef CANSERVICEMANAGER_H
#define CANSERVICEMANAGER_H
#include <memory>
#include <unordered_map>

#include "CANServiceIF.h"

class CANServiceManager {

    private:
        CANServiceManager();
        
    public:
        ~CANServiceManager();
        static CANServiceManager &GetInstance() {
            if (gInstance == nullptr) {
                gInstance = std::shared_ptr<CANServiceManager>(new CANServiceManager());
            }
            return *gInstance;
        }

    public:
        int Connect(const std::string &sckName);
        int Disconnect(const std::string &sckName);
        int Active(const std::string &sckName);
        int Deactive(const std::string &sckName);
        int Send(const std::string sckName, const can_frame_ptr &frm);
        template<typename Callable, typename ...Args>
        int RegisterReceiveCallback(const std::string &sckName, Callable &&callback, Args &&... _args) {
            CANServiceIFPtr canSrv = nullptr;
            try {
                canSrv = mConnectedDevs.at(sckName);
                if (canSrv != nullptr) {
                    std::function<void(const can_frame_ptr &)> bindFunc = std::bind(std::forward<Callable>(callback),
                                                                                    std::placeholders::_1,
                                                                                    std::forward<Args>(_args)...);
                    canSrv->SetCallback(bindFunc);
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
    private:
        static std::shared_ptr<CANServiceManager> gInstance;
        std::unordered_map<std::string, CANServiceIFPtr> mConnectedDevs; // manage connected devices by name
};

#endif // CANSERVICEMANAGER_H
