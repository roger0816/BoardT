#ifndef ITEMACTIONRUN_H
#define ITEMACTIONRUN_H

#include <QWidget>
#include "ItemPic.h"
#include "Global.h"

class ItemActionRun : public ItemPic
{
    Q_OBJECT
public:
    explicit ItemActionRun(QWidget *parent = nullptr);

    bool init() override;

    void mousePressEvent(QMouseEvent *e) override;

    void timerEvent(QTimerEvent *) override;


    QStringList m_listPic;

    QStringList m_listUrl;

    int m_iIdx = 0;

    int m_iChangeSec=1;

    bool m_bStop = false;

    QRect m_popRect;

signals:

public slots:
};

#endif // ITEMACTIONRUN_H
