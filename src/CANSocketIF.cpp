/*****************************************************************************
    CANSocketIF

    Created: 17 2019 by quynhpp

    Copyright 2019 quynhpp. All rights reserved.

    This file may be distributed under the terms of GNU Public License version
    3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
    license should have been included with this file, or the project in which
    this file belongs to. You may also find the details of GPL v3 at:
    http://www.gnu.org/licenses/gpl-3.0.txt

    If you have any questions regarding the use of this file, feel free to
    contact the author of this file, or the owner of the project in which
    this file belongs to.
 *****************************************************************************/
#include "CANSocketIF.h"
#include "Debug.h"
#include <net/if.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include <poll.h>
#include <string.h>
#include <memory>
#include "SystemDefine.h"

CANSocketIF::CANSocketIF() :
    mSocketFd(0),
    mPortName("") {

}

CANSocketIF::~CANSocketIF() {
    Disconnect();
}

int CANSocketIF::Connect(const std::__cxx11::string portName) {
    mPortName = portName;
    struct ifreq ifr;
    // Open socket
    if ((mSocketFd = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("ERR: Can connect failed.");
        return S_ERR;
    }
    strncpy(ifr.ifr_name, mPortName.c_str(), IFNAMSIZ - 1);
    ifr.ifr_name[IFNAMSIZ - 1] = '\0';
    ifr.ifr_ifindex = if_nametoindex(ifr.ifr_name);
    if (!ifr.ifr_ifindex) {
        perror("ERR: if_nametoindex");
        close(mSocketFd);
        return S_ERR;
    }
    memset(&mCANAddr, 0, sizeof(mCANAddr));
    mCANAddr.can_family = AF_CAN;
    mCANAddr.can_ifindex = ifr.ifr_ifindex;

    if (bind(mSocketFd, (struct sockaddr *) &mCANAddr, sizeof(mCANAddr)) < 0) {
        close(mSocketFd);
        return S_ERR;
    }
    std::cout << "[INFO]: connected to " << mPortName << "\n";
    return S_OK;
}

int CANSocketIF::Disconnect() {
    if (close(mSocketFd) != 0) {
        return S_ERR;
    }
    mSocketFd = 0;
    return S_OK;
}

int CANSocketIF::SendFrame(const can_frame_ptr &frame) {
    int ret = write(mSocketFd, frame.get(), sizeof(can_frame));
    if (ret != sizeof(can_frame)) {
        WRN_MSG("WRN: Can send failed.\n");
        return S_ERR;
    }
    return S_OK;
}

int CANSocketIF::ReadFrame(can_frame_ptr &frame) {
    struct iovec iov;
    struct msghdr msg;
    struct cmsghdr *cmsg;
    char ctrlmsg[CMSG_SPACE(sizeof(struct timeval)) + CMSG_SPACE(sizeof(__u32))];
    struct timeval tv       = {0, 0};
    iov.iov_base            = frame.get();
    iov.iov_len             = sizeof(can_frame);
    msg.msg_name            = &mCANAddr;
    msg.msg_namelen         = sizeof(mCANAddr);
    msg.msg_iov             = &iov;
    msg.msg_iovlen          = 1;
    msg.msg_control         = &ctrlmsg;
    msg.msg_controllen      = sizeof(ctrlmsg);
    msg.msg_flags           = 0;
    int r = recvmsg(mSocketFd, &msg, MSG_DONTWAIT);
    if (r <= 0) {
        return S_ERR;
    }
    for (cmsg = CMSG_FIRSTHDR(&msg); cmsg && (cmsg->cmsg_level == SOL_SOCKET); cmsg = CMSG_NXTHDR(&msg, cmsg)) {
        if (cmsg->cmsg_type == SO_TIMESTAMP) {
            tv = *(struct timeval *)CMSG_DATA(cmsg);
        }
    }
    if (frame->can_id & CAN_ERR_FLAG) {
        return S_ERR;   //notify error
    }
    return S_OK;
}

int CANSocketIF::AcquireData(int timeout) const {
    struct pollfd p[1];
    p[0].fd = mSocketFd;
    p[0].events = POLLIN;
    int t = poll(p, 1, timeout);
    return (t & POLLIN) ? S_OK : S_ERR;
}

int CANSocketIF::SocketFD() const {
    return mSocketFd;
}
