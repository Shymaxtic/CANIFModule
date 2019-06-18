/*****************************************************************************
 * libcanifmodule_global.h
 *
 * Created: 18 2019 by shymaxtic
 *
 * Copyright 2019 shymaxtic. All rights reserved.
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
#ifndef LIBCANIFMODULE_GLOBAL_H
#define LIBCANIFMODULE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBCANIFMODULE_LIBRARY)
#  define LIBCANIFMODULESHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBCANIFMODULESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBCANIFMODULE_GLOBAL_H
