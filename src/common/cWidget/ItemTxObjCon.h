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

    int m_iPlaySpeed=5;

    int m_iReadSpeed=2;

    int m_iSec=0;

    void doRead();

    void doChangeShow();

    bool m_bIsShowValue = true;

    int m_iLimitMin=1;

    int m_iLimitMax=100;

    int m_iSelect =0;

    QString m_sMsg1="";

    QString m_sMsg2="";

    QString m_sCurrentValue;

    QString m_sCurrentMsg;

    QFile m_file;

    QTimer m_timer;

signals:

public slots:
    void slotTimer();

};

#endif // ITEMTXOBJCON_H
