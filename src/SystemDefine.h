/*****************************************************************************
    SystemDefine.h

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
#ifndef SYSTEMDEFINE_H
#define SYSTEMDEFINE_H
#include <linux/can.h>
#include <memory>
#include <deque>
#define UT_INFO

#ifdef UT_INFO
#define UT_VIRTUAL     virtual
#else
#define UT_VIRTUAL
#endif


#define S_OK                    0
#define S_ERR                   -1


// Semaphore
#define S_SEM_OVERMAX           S_OK + 1
#define S_SEM_TIMEOUT           S_ERR - 1


typedef std::shared_ptr<can_frame>  can_frame_ptr;
typedef std::deque<can_frame_ptr>   can_frame_list;

#endif // SYSTEMDEFINE_H
