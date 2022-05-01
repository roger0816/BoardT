#-------------------------------------------------
#
# Project created by QtCreator 2021-01-04T23:52:51
#
#-------------------------------------------------

QT       += core gui




greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ActiveBoard
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

MOC_DIR =$$PWD/obj
OBJECTS_DIR =$$PWD/obj
UI_DIR =$$PWD/obj
DESTDIR =$$PWD/../../bin/
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32{
CONFIG+=DEVELOP
}

CONFIG(HALF) {
DEFINES +=HALF
}

CONFIG(DEVELOP) {
DEFINES +=DEVELOP
QT += multimedia
QT += multimediawidgets
}
else {
QT       += webkitwidgets
DEFINES +=WEB
DEFINES +=VLC
DEFINES += RX_MODIFY

LIBS += -lwiringPi

INCLUDEPATH +=$$PWD/../lib/Pn532-nfc-hat-code/raspberrypi/c

HEADERS += \
../lib/Pn532-nfc-hat-code/raspberrypi/c/pn532.h \
../lib/Pn532-nfc-hat-code/raspberrypi/c/pn532_rpi.h \

SOURCES += \
../lib/Pn532-nfc-hat-code/raspberrypi/c/pn532.c \
../lib/Pn532-nfc-hat-code/raspberrypi/c/pn532_rpi.c \


}



INCLUDEPATH +=$$PWD/../bin/data
INCLUDEPATH +=$$PWD/../lib



include($$PWD/../lib/RpkLib/RpkPlayer.pri)
!win32{
include($$PWD/../lib/udev/udev.pri)
}



CONFIG += c++11

SOURCES += \
    DialogPainter.cpp \
    FuncNfc.cpp \
    FuncUsb.cpp \
        main.cpp \
        widget.cpp \
    Global.cpp \
    DialogPop.cpp \
    LayerUsbUpdate.cpp


HEADERS += \
    DialogPainter.h \
    FuncNfc.h \
    FuncUsb.h \
        widget.h \
    Global.h \
    DialogPop.h \
    LayerUsbUpdate.h


FORMS += \
    DialogPainter.ui \
        widget.ui \
    DialogPop.ui \
    LayerUsbUpdate.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


include($$PWD/../lib/RpkLib/qrencode/qrencode.pri)
INCLUDEPATH+=$$PWD/../lib/RpkLib/qrencode/

include($$PWD/../common/component/Component.pri);
include($$PWD/../common/Common.pri);

RESOURCES += \
    res/res.qrc


