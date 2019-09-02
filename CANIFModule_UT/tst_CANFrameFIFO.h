/*****************************************************************************
    tst_CANFrameFIFO.h

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
#ifndef TST_CANFRAMEFIFO_H
#define TST_CANFRAMEFIFO_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#define private public

using namespace testing;

#include "CANFrameFIFO.h"

// Test push - pop
TEST(CANFrameFIFO1, CANIFModuleTestSet) {
    CANFrameFIFO testCANFrameFIFO1;
    for (uint8_t i = 0; i < 129; ++i) {
        can_frame_ptr canfr(new can_frame);
        canfr->can_id = i;
        testCANFrameFIFO1.Push(canfr);
        can_frame_ptr canfrread;
        testCANFrameFIFO1.Pop(canfrread);
        EXPECT_EQ(canfrread->can_id, i);
    }
    EXPECT_EQ(testCANFrameFIFO1.mFrames.size(), 0);
}

// Test clear.
TEST(CANFrameFIFO2, CANIFModuleTestSet) {
    CANFrameFIFO testCANFrameFIFO1;
    for (uint8_t i = 0; i < 10; ++i) {
        can_frame_ptr canfr(new can_frame);
        testCANFrameFIFO1.Push(canfr);
    }
    EXPECT_EQ(testCANFrameFIFO1.mFrames.size(), 10);
    testCANFrameFIFO1.Clear();
    EXPECT_EQ(testCANFrameFIFO1.mFrames.size(), 0);
}

// Test push over maximum allow.
//TEST(CANFrameFIFO3, CANIFModuleTestSet) {
//    CANFrameFIFO testCANFrameFIFO1;
//    for (uint8_t i = 0; i < 129; ++i) {
//        can_frame_ptr canfr(new can_frame);
//        canfr->can_id = i;
//        testCANFrameFIFO1.Push(canfr);
//    }
//}

// Test push
TEST(CANFrameFIFO4, CANIFModuleTestSet) {
    CANFrameFIFO testCANFrameFIFO1;
    for (uint8_t i = 0; i < 128; ++i) {
        can_frame_ptr canfr(new can_frame);
        testCANFrameFIFO1.Push(canfr);
    }
    EXPECT_EQ(testCANFrameFIFO1.mFrames.size(), 128);
}

// Test push all - pop all
TEST(CANFrameFIFO5, CANIFModuleTestSet) {
    CANFrameFIFO testCANFrameFIFO1;
    for (uint8_t i = 0; i < 128; ++i) {
        can_frame_ptr canfr(new can_frame);
        testCANFrameFIFO1.Push(canfr);
    }
    EXPECT_EQ(testCANFrameFIFO1.mFrames.size(), 128);
    std::vector<can_frame_ptr> actualResult;
    while (testCANFrameFIFO1.mFrames.empty() == false) {
        can_frame_ptr canfr(new can_frame);
        testCANFrameFIFO1.Pop(canfr);
        actualResult.push_back(canfr);
    }
    EXPECT_EQ(actualResult.size(), 128);
}
#endif // TST_CANFRAMEFIFO_H
