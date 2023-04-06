QT       += core gui
TEMPLATE = lib
CONFIG += staticlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
    mainwindow.cpp bookmark.cpp	drawelementwidget.cpp	generationhandler.cpp	groupbookmark.cpp	time_line.cpp	viewhandler.cpp

HEADERS += \
    mainwindow.h	bookmark.h	drawelementwidget.h	generationhandler.h	groupbookmark.h	profile.h	time_line.h	timelineitem.h	viewhandler.h

FORMS += \
    mainwindow.ui dialog.ui
