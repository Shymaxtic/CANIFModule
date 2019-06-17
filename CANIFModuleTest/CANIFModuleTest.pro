TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    CANIF.cpp \
    CANService.cpp \
    CANSocketIF.cpp \
    ReceiveChannel.cpp \
    TransmitChannel.cpp

HEADERS += \
    CANIF.h \
    CANService.h \
    CANSocketIF.h \
    Debug.h \
    ReceiveChannel.h \
    CANIFModule.h \
    TransmitChannel.h

QMAKE_CXXFLAGS += -std=c++0x -pthread
LIBS += -pthread
