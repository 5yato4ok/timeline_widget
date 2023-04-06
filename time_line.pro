TEMPLATE = subdirs

SUBDIRS += \
    timeline_core \
    launcher \
    tests

tests.depends = timeline_core
launcher.depends = timeline_core
