QT       += core gui

INCLUDEPATH +=$$PWD


CONFIG(DEVELOP){
}
else{
LIBS += -lvlc -lX11

}

# Input

HEADERS += \
    $$PWD/CPlayer.h

SOURCES += \
    $$PWD/CPlayer.cpp
