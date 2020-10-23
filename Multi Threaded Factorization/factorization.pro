TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bdundle
CONFIG -= qt

SOURCES += main.cpp


unix|win32: LIBS += -lwsock32
