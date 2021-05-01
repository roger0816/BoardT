INCLUDEPATH+=$$PWD \
    $$PWD/cData \
    $$PWD/cWidget

HEADERS += \
    $$PWD/cData/CData.h \
    $$PWD/cData/LayerData.h \
    $$PWD/cData/ObjData.h \
    $$PWD/cData/Voj.h \
    $$PWD/cWidget/DisplayWidget.h \
    $$PWD/cWidget/ItemBaseContent.h \
    $$PWD/cWidget/ItemLabel.h

SOURCES += \
    $$PWD/cData/CData.cpp \
    $$PWD/cData/LayerData.cpp \
    $$PWD/cData/ObjData.cpp \
    $$PWD/cWidget/DisplayWidget.cpp \
    $$PWD/cWidget/ItemBaseContent.cpp \
    $$PWD/cWidget/ItemLabel.cpp

FORMS += \
    $$PWD/cWidget/DisplayWidget.ui \
    $$PWD/cWidget/ItemBaseContent.ui \
    $$PWD/cWidget/ItemLabel.ui




