QT += widgets testlib

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += $$PWD/../timeline_core
INCLUDEPATH += $$OUT_PWD/../timeline_core

SOURCES +=  tst_test_generation.cpp
include($$PWD/../timeline_core/timeline_core.pri)
