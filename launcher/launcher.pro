QT += gui widgets
TEMPLATE = app
CONFIG += c++17
INCLUDEPATH += $$PWD/../timeline_core
INCLUDEPATH += $$OUT_PWD/../timeline_core

SOURCES += main.cpp

include($$PWD/../timeline_core/timeline_core.pri)
