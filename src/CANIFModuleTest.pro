TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp  \
    CANChannel.cpp \
    CANFrameFIFO.cpp \
    CANReceiveChannel.cpp \
    CANServiceIF.cpp \
    CANServiceManager.cpp \
    CANSocketIF.cpp \
    CANTransmitChannel.cpp \
    Semaphore.cpp

HEADERS += \
    CANChannel.h \
    CANFrameFIFO.h \
    CANIFModule.h \
    CANReceiveChannel.h \
    CANServiceIF.h \
    CANServiceManager.h \
    CANSocketIF.h \
    CANTransmitChannel.h \
    Debug.h \
    Semaphore.h \
    SystemDefine.h

QMAKE_CXXFLAGS += -std=c++0x -pthread
LIBS += -pthread
