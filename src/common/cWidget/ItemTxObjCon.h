#ifndef ITEMTXOBJCON_H
#define ITEMTXOBJCON_H

#include <QApplication>
#include <QWidget>
#include "ItemLabel.h"
#include <QTimerEvent>
#include <QFile>
#include <QTimer>




class ItemTxObjCon : public ItemLabel
{
    Q_OBJECT
public:
    explicit ItemTxObjCon(QWidget *parent = nullptr);

    void timerEvent(QTimerEvent *) override;

   void updateItem() override;

   enum status{_MIN=0,_NORMAL,_MAX} ;

    int m_iPlaySpeed=5;

    int m_iReadSpeed=2;

    int m_iGpioSpeed=2;

    int m_iSec=0;

    void doRead();

    void doChangeShow();

    bool m_bIsShowValue = true;

    double m_iLimitMin=1.00;

    double m_iLimitMax=100;

    int m_iSelect =0;

    QString m_sMsgMin="";

    QString m_sMsg="";

    QString m_sMsgMax="";

    QString m_sCurrentValue;

    QString m_sCurrentMsg;

    QFile m_file;

    QTimer m_timer;

    void setStatusStyle(int i);

    QList<int> m_listGpioPin;

    QList<int> m_listGpioValue;

    bool m_changeGpio = false;

    void setGpio(int iPin);

    void sendGpio(int iPin, int iValue);

    int m_status=1;
signals:

public slots:
    void slotTimer();

};

#endif // ITEMTXOBJCON_H
