#ifndef FUNCNFC_H
#define FUNCNFC_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QThread>

#ifdef DEVELOP
class FuncNfc : public QThread
{
    Q_OBJECT
public:
    explicit FuncNfc(QObject *parent = nullptr):QThread(parent){}
    bool m_bStop=false;
    QString getUid(){return "";}
signals:
    void hoverUid(QString);
};
#else


#include <stdio.h>
#include <stdint.h>
#include <time.h>
extern "C" {
#include "pn532.h"
#include "pn532_rpi.h"
}



class FuncNfc : public QThread
{
    Q_OBJECT
public:
    explicit FuncNfc(QObject *parent = nullptr);

    QString getUid(){return m_sPreUid;}

    bool m_bStop = false;
private:
    uint8_t buff[255];
    uint8_t uid[MIFARE_UID_MAX_LENGTH];
    int32_t uid_len = 0;

    void run() override;
    PN532 pn532;

    bool bFindDevice = false;

    QString m_sPreUid="";

    QString m_sCurrentUid="";
signals:
    void hoverUid(QString sUid);

};


#endif

#endif // FUNCNFC_H
