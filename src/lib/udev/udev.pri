unix:LIBS += -ludev -lm

INCLUDEPATH += $$PWD
HEADERS += \
    $$PWD/udev.h \
    $$PWD/udevdevice.h \
    $$PWD/udevmonitor.h
SOURCES += \
    $$PWD/udev.cpp \
    $$PWD/udevdevice.cpp \
    $$PWD/udevmonitor.cpp
