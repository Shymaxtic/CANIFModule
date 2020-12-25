/*****************************************************************************
    %{Cpp:License:FileName}

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
#ifndef TST_CANIFMODULETESTCASE_H
#define TST_CANIFMODULETESTCASE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>


#define private public

using namespace testing;
#include "SystemDefine.h"
#include "Semaphore.h"

TEST(Semaphore, CANIFModuleTestSet) {
    Semaphore<> testSem1;
    EXPECT_EQ(testSem1.mCnt, 0);
    EXPECT_EQ(testSem1.mMaxCnt, 1);
}

TEST(Semaphore2, CANIFModuleTestSet) {
    try {
        Semaphore<0> testSem1(0);
    }
    catch (std::invalid_argument &e) {
        EXPECT_EQ(e.what(), std::string("max count must greater than 0."));
    }
}

TEST(Semaphore3, CANIFModuleTestSet) {
    Semaphore<1> testSem1(1);
    testSem1.Acquire();
    EXPECT_EQ(testSem1.mCnt, 0);
}

TEST(Semaphore4, CANIFModuleTestSet) {
    Semaphore<1> testSem1(0);
    testSem1.Release();
    EXPECT_EQ(testSem1.mCnt, 1);
}

TEST(Semaphore5, CANIFModuleTestSet) {
    Semaphore<1> testSem1(1);
    testSem1.Release();
    EXPECT_EQ(testSem1.mCnt, testSem1.mMaxCnt);
}

TEST(Semaphore6, CANIFModuleTestSet) {
    Semaphore<1> testSem1(0);
    int test = testSem1.Acquire(1000);
    EXPECT_EQ(test, S_SEM_TIMEOUT);
}


#endif // TST_CANIFMODULETESTCASE_H
