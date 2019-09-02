TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp  \
    ../src/CANChannel.cpp \
    ../src/CANFrameFIFO.cpp \
    ../src/CANReceiveChannel.cpp \
    ../src/CANServiceIF.cpp \
    ../src/CANServiceManager.cpp \
    ../src/CANSocketIF.cpp \
    ../src/CANTransmitChannel.cpp \
    ../src/Semaphore.cpp

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
    ../src/SystemDefine.h


INCLUDEPATH += ../src

DEPENDPATH += ../src


QMAKE_CXXFLAGS += -std=c++0x -pthread
LIBS += -pthread
