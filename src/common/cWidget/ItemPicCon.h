#ifndef ITEMPICCON_H
#define ITEMPICCON_H

#include <QWidget>
#include "ItemBaseObj.h"
#include <QTimerEvent>
#include <QResizeEvent>
#include <QShowEvent>
#include <QImageReader>

namespace Ui {
class ItemPicCon;
}

class ItemPicCon : public ItemBaseObj
{
    Q_OBJECT

public:
    explicit ItemPicCon(QWidget *parent = nullptr);
    ~ItemPicCon();

    void updateItem() override;

    void timerEvent(QTimerEvent *) override;



private:
    Ui::ItemPicCon *ui;

    int m_iSecCount = 0;

    int m_iIdx=0;
};

#endif // ITEMPICCON_H
