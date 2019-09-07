/*****************************************************************************
    tst_CANReceiveChannel.h

    Created: 02 2019 by shymaxtic

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
#ifndef TST_CANRECEIVECHANNEL_H
#define TST_CANRECEIVECHANNEL_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#define private public
#define protected public

using namespace testing;
//#define UT_INFO

#include "CANReceiveChannel.h"
#include "CANServiceIF.h"
#include "CANSocketIF.h"
#include <vector>
#include "Debug.h"

static std::vector<can_frame_ptr> rcvActualResult;
static CANReceiveChannel *testCANRcvCh = nullptr;
class RCVTestDummyCANServiceIF : public CANServiceIF {
    public:
        RCVTestDummyCANServiceIF() {}
        int Receive(const can_frame_ptr &frm) override {
            rcvActualResult.push_back(frm);
            return S_OK;
        }
};

class RCVTestDummyCANSocketIF : public CANSocketIF {
    public:
        RCVTestDummyCANSocketIF() {}
        int AcquireData(int timeout) const override {
            usleep(100);
            return S_OK;
        }
        int ReadFrame(can_frame_ptr &frame) override {
            return testCANRcvCh->Read(frame);
        }
};

static RCVTestDummyCANServiceIF RCVTestdummyCANSrvIF;
static RCVTestDummyCANSocketIF  RCVTestdummyCANSckIF;



// Test init.
TEST(CANReceiveChannel0, CANIFModuleTestSet) {
    try {
        testCANRcvCh = new CANReceiveChannel(nullptr, nullptr);
    }
    catch (std::invalid_argument &e) {
        EXPECT_EQ(e.what(), std::string("nullptr is not permitted."));
    }
    testCANRcvCh = new CANReceiveChannel(&RCVTestdummyCANSrvIF, &RCVTestdummyCANSckIF);
    EXPECT_NE(testCANRcvCh, nullptr);
}

// Test start.
TEST(CANReceiveChannel1, CANIFModuleTestSet) {
    int test = testCANRcvCh->Start();
    EXPECT_EQ(test, S_OK);
}

// Test read.
TEST(CANReceiveChannel2, CANIFModuleTestSet) {
    rcvActualResult.clear();
    std::vector<can_frame_ptr> expectResult;
    for (uint8_t i = 0; i < 128; ++i) {
        can_frame_ptr frm(new can_frame);
        expectResult.push_back(frm);
        frm->can_id = i;
        frm->can_dlc = 8;
        testCANRcvCh->Write(frm);
    }
    usleep(100000);
    EXPECT_EQ(rcvActualResult.size(), expectResult.size());
    for (uint8_t i = 0; i < 128; ++i) {
        EXPECT_EQ(rcvActualResult[i]->can_id, i);
        EXPECT_EQ(rcvActualResult[i]->can_dlc, 8);
    }
}

// Test stop.
TEST(CANReceiveChannel3, CANIFModuleTestSet) {
    int test = testCANRcvCh->Stop();
    EXPECT_EQ(test, S_OK);
}

#endif // TST_CANRECEIVECHANNEL_H
