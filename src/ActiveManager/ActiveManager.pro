QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

MOC_DIR =$$PWD/obj
OBJECTS_DIR =$$PWD/obj
UI_DIR =$$PWD/obj
DESTDIR =$$PWD/../../bin/



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

SOURCES += \
    DialogMsg.cpp \
    LayerAddContent.cpp \
    LayerEditor.cpp \
    LayerSelector.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    DialogMsg.h \
    LayerAddContent.h \
    LayerEditor.h \
    LayerSelector.h \
    widget.h

FORMS += \
    DialogMsg.ui \
    LayerAddContent.ui \
    LayerEditor.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



include($$PWD/../lib/RpkLib/RpkPlayer.pri)



include($$PWD/editTool/editTool.pri);


include($$PWD/../common/Common.pri);





