#ifndef VOJ_H
#define VOJ_H


#include <QList>
#include <QDateTime>
#include <QString>
#include <QColor>
#include <QDebug>
#include <QFileInfoList>
#include <QFileInfo>
#include <QSettings>
#include <QDir>
#include <QFont>
#include <QPixmap>


static QString E_TEXT = "text";

static QString E_PIC= "pic";

static QString E_BUTTON ="button";

static QString E_DATETIME ="dateTime";

static QString E_WEB ="web";

static QString E_FUNCTION ="function";

static QString E_VIDEO ="video";

static QString E_MARQUEE = "marquee";

static QString E_QRCODE = "qrcode";


// cmd
static QString CMD_None ="";

static QString CMD_Page = "page";

static QString CMD_PageNoStop = "pageNoStopVideo";

static QString CMD_Pop ="pop";

static QString CMD_Change="change";

static QString CMD_Gpio="gpio";

static QString CMD_Script="script";


enum
{
    ADD_BTN_TEXT=0,
    ADD_BTN_PIC,
    ADD_BTN_VIDEO,
    ADD_BTN_BTN,
    ADD_BTN_MARQUEE,
    ADD_BTN_QR

};


struct DataLayer
{
    QTime timeScheduleFrom;

    QTime timeScheduleTo;

    int dayOfWeek = 1;

    bool bStopPreVideo = true;

};


struct DataModel
{
    QString sTarget="def";

    bool bStopVideoChange = false;

    QDateTime updateDateTime;

    QDateTime sleepFrom;

    QDateTime sleepTo;

    bool bEnableSleepModel = false;

};



struct DataText
{
    DataText()
    {
        font.fromString("Arial,24,-1,5,50,0,0,0,0,0,Regular");
    }

    QString sText="Label";

    int iPixSize=32;

    QFont font;

    bool bIsCent=true;

    QColor textColor = QColor(0,0,0,255);

    QColor bgColor = QColor(255,255,255,255);

    QString m_sImagePath;

    QString m_sCmdPath;

    int m_sMarSpeed = 5;

    QStringList sListText;


};



struct DataPic
{
    int iSec = 10;

    QList<QPixmap> listPic;

    QStringList listPicName;


};

struct DataVideo
{
   // int iSec = 10;


    QStringList listName;


};

struct DataMar
{
    QStringList listText;

    int iSpeed = 3;
};

struct DataCmd
{
    QString sCmd="";

    QString sValue1="";

    QString sValue2="";


};


#endif // VOJ_H
