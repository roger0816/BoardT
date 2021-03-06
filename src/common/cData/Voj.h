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

static QString E_URL ="web";

static QString E_FUNCTION ="function";

static QString E_VIDEO ="video";

static QString E_MARQUEE = "marquee";

static QString E_QRCODE = "qrcode";

static QString E_TXVALUE = "txValue";

static QString E_GRID = "grid";

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
    ADD_BASIC_TEXT =0,
    ADD_BASIC_PIC,
    ADD_BASIC_VIDEO,
    ADD_BASIC_MARQUEE,
    ADD_BASIC_DATETIME,
    ADD_BASIC_URL,
    ADD_BASIC_QR,

    ADD_ADV_BUTTON,
    ADD_ADV_MEDIA,
    ADD_ADV_964,
    ADD_ADV_PAINTER,
    ADD_ADV_TXT,
    ADD_ADV_TICKET,
    ADD_ADV_ORDER


};

enum _SCHEDULE_Mode
{
    SCHEDULE_OFF = 0,
    SCHEDULE_ON =1,
    SCHEDULE_TIME
};


struct DataLayer
{
    QTime timeScheduleFrom;

    QTime timeScheduleTo;

    int dayOfWeek = 1;

    bool bStopPreVideo = true;

    QList<QVariant> listObjSort;

};


struct DataModel
{
    QString sTarget="def";

    int iScheduleMode = SCHEDULE_OFF;


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


struct DataSchedule
{
    QString sDef="def";




};


struct DataPic
{
    int iSec = 10;

    QList<QPixmap> listPic;

    QStringList listPicName;

    QStringList listOriginPath;


};

struct DataVideo
{
    // int iSec = 10;


    QStringList listName;

    QString sRtsp = "";

    bool bIsMute = false;

    bool bUseFile = true;

    bool bHasChange = false;

};

struct DataGrid
{
    // int iSec = 10;
    DataGrid()
    {
        for(int i=0;i<9;i++)
        {
            listG1.append("");

            QStringList listItemG2;

            QStringList listItemG3;
            for(int j=0;j<9;j++)
            {
                listItemG2.append("");

                listItemG3.append("");
            }
            listG2[i] = listItemG2;

            listG3[i] = listItemG3;
        }
    }


    QStringList listG1;  //grid layer level 1

    QStringList listG2[9];

    QStringList listG3[9];

    int iCount =9;

    bool bHasChange = false;

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

//=====

namespace Label {

static QString font="font";

static QString text="text";

static QString alignCenter="alignCenter";

static QString bgColor="bgColor";

static QString txtColor="txtColor";

static QString imagePath="imagePath";

}

namespace Btn {

static QString btnType="btnType";

static QString btnTypeNote="btnTypeNote";

static QString btnStopPlay ="btnStopPlay";

static QString btnInput="btnInput";

static QString btnOpuput="btnOutput";

static QString btnText2="btnText2";


}

namespace Marquee
{
static QString speed="speed";

static QString listText ="listText";
}

namespace DateTime
{
static QString speed="dateSpeed";

static QString dateStr ="dateStr";

static QString timeStr ="timeStr";
}

namespace Url {
static QString source="urlSource";
}

namespace  TxtValue{

static QString readSpeed="readSpeed";

static QString playSpeed="playSpeed";

static QString index="index";


static QString max="max";


static QString min="min";


static QString msg="msg";

static QString font="font";

static QString alignCenter="alignCenter";

static QString bgColor="bgColor";

static QString txtColor="txtColor";

static QString imagePath="imagePathNormal";

static QString fontMin="fontMin";

static QString alignCenterMin="alignCenterMin";

static QString bgColorMin="bgColorMin";

static QString txtColorMin="txtColorMin";

static QString imagePathMin="imagePathMin";

static QString fontMax="fontMax";

static QString alignCenterMax="alignCenterMax";

static QString bgColorMax="bgColorMax";

static QString txtColorMax="txtColorMax";

static QString imagePathMax="imagePathMax";

static QString gpioPin="gpioPin";

static QString gpioPinMin="gpioPinMin";

static QString gpioPinMax="gpioPinMax";

static QString gpioValue="gpioValue";

static QString gpioValueMin="gpioValueMin";

static QString gpioValueMax="gpioValueMax";



}


#endif // VOJ_H
