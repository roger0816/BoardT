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
else {
QT       += webkitwidgets
DEFINES +=WEB
DEFINES +=VLC

LIBS += -lwiringPi

INCLUDEPATH +=$$PWD/../lib/Pn532-nfc-hat-code/raspberrypi/c

HEADERS += \
../lib/Pn532-nfc-hat-code/raspberrypi/c/pn532.h \
../lib/Pn532-nfc-hat-code/raspberrypi/c/pn532_rpi.h \

SOURCES += \
../lib/Pn532-nfc-hat-code/raspberrypi/c/pn532.c \
../lib/Pn532-nfc-hat-code/raspberrypi/c/pn532_rpi.c \


}


INCLUDEPATH+= uiItem \
              cEdit


SOURCES += \
    DialogEditGrid.cpp \
    DialogMsg.cpp \
    DialogSelectFile.cpp \
    DialogUploadUsb.cpp \
    LayerAction.cpp \
    LayerAddContent.cpp \
    LayerEditGrid.cpp \
    LayerEditor.cpp \
    LayerSchedule.cpp \
    LayerSelector.cpp \
    LayerTimeSchedule.cpp \
    StageEditArea.cpp \
    StageManager.cpp \
    cEdit/EditBase.cpp \
    cEdit/EditDateTime.cpp \
    cEdit/EditGrid.cpp \
    cEdit/EditLabel.cpp \
    cEdit/EditMar.cpp \
    cEdit/EditPic.cpp \
    cEdit/EditTxObj.cpp \
    cEdit/EditVideo.cpp \
    main.cpp \
    uiItem/IconButton.cpp \
    widget.cpp

HEADERS += \
    DialogEditGrid.h \
    DialogMsg.h \
    DialogSelectFile.h \
    DialogUploadUsb.h \
    LayerAction.h \
    LayerAddContent.h \
    LayerEditGrid.h \
    LayerEditor.h \
    LayerSchedule.h \
    LayerSelector.h \
    LayerTimeSchedule.h \
    StageEditArea.h \
    StageManager.h \
    cEdit/EditBase.h \
    cEdit/EditDateTime.h \
    cEdit/EditGrid.h \
    cEdit/EditLabel.h \
    cEdit/EditMar.h \
    cEdit/EditPic.h \
    cEdit/EditTxObj.h \
    cEdit/EditVideo.h \
    uiItem/IconButton.h \
    widget.h

FORMS += \
    DialogEditGrid.ui \
    DialogMsg.ui \
    DialogSelectFile.ui \
    DialogUploadUsb.ui \
    LayerAction.ui \
    LayerAddContent.ui \
    LayerEditGrid.ui \
    LayerEditor.ui \
    LayerSchedule.ui \
    LayerTimeSchedule.ui \
    StageEditArea.ui \
    StageManager.ui \
    cEdit/EditDateTime.ui \
    cEdit/EditGrid.ui \
    cEdit/EditLabel.ui \
    cEdit/EditMar.ui \
    cEdit/EditPic.ui \
    cEdit/EditTxObj.ui \
    cEdit/EditVideo.ui \
    uiItem/IconButton.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



include($$PWD/../lib/RpkLib/RpkPlayer.pri)



include($$PWD/editTool/editTool.pri);


include($$PWD/../common/Common.pri);


include($$PWD/../lib/RpkLib/qrencode/qrencode.pri)
INCLUDEPATH+=$$PWD/../lib/RpkLib/qrencode/

RESOURCES += \
    res/res.qrc

DISTFILES +=



