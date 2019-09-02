/*****************************************************************************
 * Debug
 *
 * Created: 17 2019 by quynhpp
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
#ifndef DEBUG_H
#define DEBUG_H

// Debug macro
#define DISABLE_DEBUG   0
#define ENABLE_DEBUG    1
#define ENABLE_DEBUG_QT 2
#define DEBUG_MOD       ENABLE_DEBUG

#if DEBUG_MOD == ENABLE_DEBUG
#include <iostream>
#define DBG_MSG(msg) do {\
        std::cerr << "[DBG]::" << __TIME__ << "::"  << __FUNCTION__ << "::" << __FILE__ << "(" << __LINE__ << "): " << msg << std::endl;\
    } while (0)

#define DBG_VAR(var) do {\
        std::cerr << "[DBG]::" << __TIME__ << "::"  << __FUNCTION__ << "::" << __FILE__ << "(" << __LINE__ << "): " << #var << " = [" << (var) << "]" << std::endl;\
    } while (0)

#define DBG_VAR_IF(A, var) do {\
        if (A) {\
            std::cerr << "[DBG]::" << __TIME__ << "::" <<  __FUNCTION__ << "::" << __FILE__ << "(" << __LINE__ << "): " << #var << " = [" << var << "]";\
        }\
    } while (0)

#define WRN_MSG(msg) do {\
        std::cerr << "[WRN]::" << __TIME__ << "::"  << __FUNCTION__ << "::" << __FILE__ << "(" << __LINE__  << "): " << msg << std::endl;\
    } while (0)

#define ERR_MSG(msg) do {\
        std::cerr << "[ERR]::" << __TIME__ << "::" << __FUNCTION__ << "::" << __FILE__ << "(" << __LINE__ << "): " << msg << std::endl;\
    } while (0)

#define DBG_MSG_IF(A, msg) do {\
        if (A) {\
            std::cerr << "[DBG]::" << __TIME__ << "::" << __FUNCTION__ << "::" << __FILE__ << "(" << __LINE__ << "): " << msg;\
        }\
    } while (0)

#elif DEBUG_MOD == ENABLE_DEBUG_QT
#include <QDebug>
#define DBG_MSG(msg) do {\
        qDebug() << "[DBG]::" << __TIME__ << __FUNCTION__ << "::" << __FILE__ << "(" << __LINE__ << "): " << msg;\
    } while (0)

#define DBG_VAR(var) do {\
        qDebug() << "[DBG]::" << __TIME__ << __FUNCTION__ << "::" << __FILE__ << "(" << __LINE__ << "): " << #var << "= [" << var << "]";\
    } while (0)

#define DBG_VAR_IF(A, var) do {\
        if (A) {\
            qDebug() << "[DBG]::" << __TIME__ << __FUNCTION__ << "::" << __FILE__ << "(" << __LINE__ << "): " << #var << "= [" << var << "]";\
        }\
    } while (0)

#define WRN_MSG(msg) do {\
        qWarning() << "[WRN]::" << __TIME__ << __FUNCTION__ << "::" << __FILE__ << "(" << __LINE__  << "): " << msg;\
    } while (0)

#define ERR_MSG(msg) do {\
        qCritical() << "[ERR]::" << __TIME__ << __FUNCTION__ << "::" << __FILE__ << "(" << __LINE__ << "): " << msg;\
    } while (0)

#define DBG_MSG_IF(A, msg) do {\
        if (A) {\
            qDebug() << "[DBG]::" << __TIME__ << __FUNCTION__ << "::" << __FILE__ << "(" << __LINE__ << "): " << msg;\
        }\
    } while (0)

#else
#define DBG_MSG(msg) do {} while (0)
#define DBG_VAR(var) do {} while (0)
#define WRN_MSG(msg) do {} while (0)
#define ERR_MSG(msg) do {} while (0)
#define DBG_MSG_IF(msg) do {} while (0)
#endif


#endif // DEBUG_H
