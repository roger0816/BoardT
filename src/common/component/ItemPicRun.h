#ifndef ITEMPICRUN_H
#define ITEMPICRUN_H


#include "ItemPic.h"
#include "Global.h"

class Global;

class ItemPicRun : public ItemPic
{
    Q_OBJECT
public:
    explicit ItemPicRun(QWidget *parent = nullptr);

    bool init() override;

    void mousePressEvent(QMouseEvent *e) override;

    void timerEvent(QTimerEvent *) override;


    QStringList m_listPic;

    int m_iIdx = 1;

    int m_iChangeSec=1;

    bool m_bStop = false;

    QRect m_popRect;


signals:

public slots:
};

#endif // ITEMPICRUN_H
