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

CONFIG -= console

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
    DialogCheckMachine.cpp \
    DialogDownload.cpp \
    DialogEditGrid.cpp \
    DialogMsg.cpp \
    DialogPicDetail.cpp \
    DialogSelectFile.cpp \
    DialogUploadNet.cpp \
    DialogUploadUsb.cpp \
    ItemCheckMachine.cpp \
    LayerAction.cpp \
    LayerAddContent.cpp \
    LayerEditGrid.cpp \
    LayerEditor.cpp \
    LayerNewModel.cpp \
    LayerSchedule.cpp \
    LayerSelector.cpp \
    StageEditArea.cpp \
    StageManager.cpp \
    cEdit/EditBase.cpp \
    cEdit/EditButton.cpp \
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
    DialogCheckMachine.h \
    DialogDownload.h \
    DialogEditGrid.h \
    DialogMsg.h \
    DialogPicDetail.h \
    DialogSelectFile.h \
    DialogUploadNet.h \
    DialogUploadUsb.h \
    ItemCheckMachine.h \
    LayerAction.h \
    LayerAddContent.h \
    LayerEditGrid.h \
    LayerEditor.h \
    LayerNewModel.h \
    LayerSchedule.h \
    LayerSelector.h \
    StageEditArea.h \
    StageManager.h \
    cEdit/EditBase.h \
    cEdit/EditButton.h \
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
    DialogCheckMachine.ui \
    DialogDownload.ui \
    DialogEditGrid.ui \
    DialogMsg.ui \
    DialogPicDetail.ui \
    DialogSelectFile.ui \
    DialogUploadNet.ui \
    DialogUploadUsb.ui \
    ItemCheckMachine.ui \
    LayerAction.ui \
    LayerAddContent.ui \
    LayerEditGrid.ui \
    LayerEditor.ui \
    LayerNewModel.ui \
    LayerSchedule.ui \
    StageEditArea.ui \
    StageManager.ui \
    cEdit/EditButton.ui \
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




include($$PWD/../common/Common.pri);


include($$PWD/../lib/RpkLib/qrencode/qrencode.pri)
INCLUDEPATH+=$$PWD/../lib/RpkLib/qrencode/

RESOURCES += \
    res/res.qrc

DISTFILES += \
    ../../bin/mvModel0.txt \
    ../../bin/reboot.txt \
    ../../bin/scrot.txt



