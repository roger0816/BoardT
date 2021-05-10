#ifndef ITEMMARCON_H
#define ITEMMARCON_H

#include <QObject>
#include "ItemBaseObj.h"
#include <QWidget>
#include <QResizeEvent>
#include <QShowEvent>
#include <QTimerEvent>
#include <QLabel>
#include <QDebug>


class ItemMarCon : public ItemBaseObj
{
    Q_OBJECT
public:
    explicit ItemMarCon(QWidget *parent = nullptr);

private:

    void timerEvent(QTimerEvent *) override;

    void reSetSize() override;

    void updateItem() override;

    int m_iIdx=0;

    QStringList m_listData;

    QWidget *m_wBg;

    QLabel *m_lb;

    int m_iSpeed = 5;

    void setText(QString st);

signals:

};

#endif // ITEMMARCON_H
