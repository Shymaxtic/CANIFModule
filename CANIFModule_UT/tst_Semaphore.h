/*****************************************************************************
 * %{Cpp:License:FileName}
 *
 * Created: 01 2019 by quynhpp
 *
 * Copyright 2019 quynhpp. All rights reserved.
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
#ifndef TST_CANIFMODULETESTCASE_H
#define TST_CANIFMODULETESTCASE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(CANIFModuleTestCase, CANIFModuleTestSet)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

#endif // TST_CANIFMODULETESTCASE_H