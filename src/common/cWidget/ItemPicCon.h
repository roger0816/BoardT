#ifndef ITEMPICCON_H
#define ITEMPICCON_H

#include <QWidget>
#include "ItemBaseObj.h"
#include <QTimerEvent>
#include <QResizeEvent>
#include <QShowEvent>

namespace Ui {
class ItemPicCon;
}

class ItemPicCon : public ItemBaseObj
{
    Q_OBJECT

public:
    explicit ItemPicCon(QWidget *parent = nullptr);
    ~ItemPicCon();


    void timerEvent(QTimerEvent *) override;

    void resizeEvent(QResizeEvent * ) override;

    void showEvent(QShowEvent *) override;


private:
    Ui::ItemPicCon *ui;

    int m_iSecCount = 0;

    int m_iIdx=0;
};

#endif // ITEMPICCON_H
