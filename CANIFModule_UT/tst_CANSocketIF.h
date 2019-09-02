/*****************************************************************************
    tst_CANSocketIF.h

    Created: 01 2019 by quynhpp

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
#ifndef TST_CANSOCKETIF_H
#define TST_CANSOCKETIF_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#define private public

using namespace testing;

#include "CANSocketIF.h"

TEST(CANSocketIF1, CANIFModuleTestSet) {
    system("sudo rmmod vcan");
    usleep(10);
    CANSocketIF canSocketIF;
    int test = canSocketIF.Connect("vcan0");
    EXPECT_EQ(test, S_ERR);
}

TEST(CANSocketIF2, CANIFModuleTestSet) {
    system("sudo modprobe vcan");
    usleep(10);
    system("sudo ip link add dev vcan0 type vcan");
    usleep(10);
    system("sudo ip link set up vcan0");
    usleep(10);

    CANSocketIF canSocketIF;
    int test = canSocketIF.Connect("vcan0");
    EXPECT_EQ(test, S_OK);

    can_frame_ptr frm(new can_frame);
    frm->can_id = 0x01;
    test = canSocketIF.SendFrame(frm);
    EXPECT_EQ(test, S_OK);

    //    test = canSocketIF.AcquireData(1000);
    //    EXPECT_EQ(test, S_OK);

    //    can_frame_ptr rcvFr(new can_frame);
    //    test = canSocketIF.ReadFrame(rcvFr);
    //    EXPECT_EQ(test, S_OK);
}

#endif // TST_CANSOCKETIF_H
