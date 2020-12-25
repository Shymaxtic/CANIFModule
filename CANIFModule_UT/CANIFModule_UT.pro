include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        ../src/CANChannel.h \
        ../src/CANFrameFIFO.h \
        ../src/CANIFModule.h \
        ../src/CANReceiveChannel.h \
        ../src/CANServiceIF.h \
        ../src/CANServiceManager.h \
        ../src/CANSocketIF.h \
        ../src/CANTransmitChannel.h \
        ../src/Debug.h \
        ../src/Semaphore.h \
        ../src/SystemDefine.h \
        tst_CANFrameFIFO.h \
        tst_CANReceiveChannel.h \
        tst_CANSocketIF.h \
        tst_CANTransmitChannel.h \
        tst_Semaphore.h

SOURCES += \
        ../src/CANChannel.cpp \
        ../src/CANFrameFIFO.cpp \
        ../src/CANReceiveChannel.cpp \
        ../src/CANServiceIF.cpp \
        ../src/CANServiceManager.cpp \
        ../src/CANSocketIF.cpp \
        ../src/CANTransmitChannel.cpp \
        main.cpp


INCLUDEPATH += ../src

DEPENDPATH += ../src

SUBDIRS += \
    ../src/CANIFModuleTest.pro

DISTFILES += \
    ../src/CANIFModuleTest.pro.user
