TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

unix:!macx: LIBS += -L$$PWD/../../build/ -lCANIFModule

INCLUDEPATH += $$PWD/../../src
DEPENDPATH += $$PWD/../../src
