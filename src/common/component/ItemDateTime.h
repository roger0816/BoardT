#ifndef ITEMDATETIME_H
#define ITEMDATETIME_H

#include <QWidget>
#include <QLabel>
#include "ItemBase.h"
#include "Global.h"
#include <QVBoxLayout>

class ItemDateTime : public ItemBase
{
    Q_OBJECT
public:
    explicit ItemDateTime(QWidget *parent = nullptr);

    bool init() override;

    void resizeEvent(QResizeEvent *) override;

    QWidget *m_wBg;

    QLabel *m_lb0;

    QLabel *m_lb1;

    void timerEvent(QTimerEvent *) override;
signals:

public slots:
};

#endif // ITEMDATETIME_H
