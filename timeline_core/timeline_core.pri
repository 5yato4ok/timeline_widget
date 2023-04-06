INCLUDEPATH += $$PWD
INCLUDEPATH += $$UI_DIR

win32 {
    CONFIG(debug, debug|release) {
        LIBS += -L$$PWD/debug -L$$OUT_PWD/../timeline_core/debug
    } else {
        LIBS += -L$$PWD/release -L$$OUT_PWD/../timeline_core/release
    }
} else {
    LIBS += -L$$PWD -L$$OUT_PWD/../timeline_core
}
LIBS += -ltimeline_core
