#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QSettings>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfoList>
#include <QFileInfo>
#include "DialogPop.h"
#include <QTimer>
#include <QShowEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QDateTime>
#include <QVBoxLayout>
#include "FuncUsb.h"
#include "qrencode.h"
#include "FuncNfc.h"
//enum TYPE
//{

//    PIC = 1,
//    WEB_VIEW,
//    DATE_TIME,
//    VIDEO ,
//    TICKET=5,
//    FUNCTION=6,
//    MARGEE=7,
//    TEXT=8,
//    PIC_ACTIVE=9,
//    PIC_RUN=10,
//    BUTTON=11

//};

static struct DEF_TYPE
{
  QString TEXT="text";

  QString PIC="pic";

  QString BUTTON="button";

  QString DATE_TIME ="dateTime";

  QString WEB_VIEW = "web";

  QString FUNCTION="function";

  QString VIDEO="video";

  //

  QString LOGO="logo";

  QString TICKET="ticket";

  QString ACTIVE="active";

  QString ON_SALE="onSale";

  QString MEDIA_CENT="mediaCent";

}TYPE;


class TouchWidget :public QWidget
{
    Q_OBJECT

public:
    explicit TouchWidget(QWidget *parent = nullptr):QWidget(parent){}

    void mousePressEvent(QMouseEvent *) override;
signals:
    void clicked();

};


class Global : public QObject
{
    Q_OBJECT
public:

    static Global &Instance();

    void destory();

    void setAllStop(bool bStop);

    bool allStop(){return m_bAllStop;}

    bool m_bAutoLayout = false;

    float m_fDiffSize =0.500;

    float m_iRealSize = 1.00;

    int m_iResumeSec = 10*1000;

    DialogPop *m_dialogPop = nullptr;


    bool isTouchLock();

    int m_iTouchLockTimer=0;

    QByteArray readFile(QString sFile);

    QString decodeColor(QString sSt);

    FuncNfc m_nfc;

    FuncUsb m_usb;
private:
    Global();



    static Global* m_pInstance;

    bool m_bAllStop = false;

    QTimer m_timer;
signals:
    void callPlay(bool bPlay);

public slots:
    void setTouch();

    void testNfc(QString sUid);

};

#endif // GLOBAL_H
