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

    void resizeEvent(QResizeEvent *) override;

    void showEvent(QShowEvent *) override;

    void reSetSize();

    int m_iIdx;

    QWidget *m_wBg;

    QLabel *m_lb;

signals:

};

#endif // ITEMMARCON_H
