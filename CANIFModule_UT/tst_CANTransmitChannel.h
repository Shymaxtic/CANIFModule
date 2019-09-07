/*****************************************************************************
    tst_CANTransmitChannel.h

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
#ifndef TST_CANTRANSMITCHANNEL_H
#define TST_CANTRANSMITCHANNEL_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#define private public

using namespace testing;
//#define UT_INFO

#include "CANTransmitChannel.h"
#include "CANServiceIF.h"
#include "CANSocketIF.h"
#include <vector>
#include "Debug.h"


static std::vector<can_frame_ptr> trmActualResult;

class DummyCANSocketIF : public CANSocketIF {
    public:
        DummyCANSocketIF() {}
        int SendFrame(const can_frame_ptr &frame)  override {
            trmActualResult.push_back(frame);
            return S_OK;
        }
};

static CANServiceIF dummyCANSrvIF;
static DummyCANSocketIF  dummyCANSckIF;
static CANTransmitChannel *testCanTrnCh = nullptr;


// Test init.
TEST(CANTransmitChannel0, CANIFModuleTestSet) {
    try {
        testCanTrnCh = new CANTransmitChannel(nullptr, nullptr);
    }
    catch (std::invalid_argument &e) {
        EXPECT_EQ(e.what(), std::string("nullptr is not permitted."));
    }
    testCanTrnCh = new CANTransmitChannel(&dummyCANSrvIF, &dummyCANSckIF);
    EXPECT_NE(testCanTrnCh, nullptr);
}

// Test start.
TEST(CANTransmitChannel1, CANIFModuleTestSet) {
    int test = testCanTrnCh->Start();
    EXPECT_EQ(test, S_OK);
}

// Test write.
TEST(CANTransmitChannel2, CANIFModuleTestSet) {
    trmActualResult.clear();
    std::vector<can_frame_ptr> expectResult;
    for (uint8_t i = 0; i < 128; ++i) {
        can_frame_ptr frm(new can_frame);
        expectResult.push_back(frm);
        frm->can_id = i;
        frm->can_dlc = 8;
        testCanTrnCh->Write(frm);
    }
    usleep(5000);
    EXPECT_EQ(trmActualResult.size(), expectResult.size());
    for (uint8_t i = 0; i < 128; ++i) {
        EXPECT_EQ(trmActualResult[i]->can_id, i);
        EXPECT_EQ(trmActualResult[i]->can_dlc, 8);
    }
}

// Test stop.
TEST(CANTransmitChannel3, CANIFModuleTestSet) {
    int test = testCanTrnCh->Stop();
    EXPECT_EQ(test, S_OK);
}


#endif // TST_CANTRANSMITCHANNEL_H
