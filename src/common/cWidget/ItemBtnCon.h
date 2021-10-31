#ifndef ITEMBTNCON_H
#define ITEMBTNCON_H

#include <QWidget>
#include "ItemLabel.h"
#include <QShowEvent>
#include <QMouseEvent>
#include "CCtrlFunc.h"
namespace Ui {
class ItemBtnCon;
}




class ItemBtnCon : public ItemLabel
{
    Q_OBJECT

public:
    explicit ItemBtnCon(QWidget *parent = nullptr);


    ~ItemBtnCon();

    void setLbStyle(QString sTxtColorKey,QString sBgColorKey,QString sImagePathKey,QString sFontKey,QString sCentKey) override;

    void mousePressEvent(QMouseEvent *) override;

    void mouseReleaseEvent(QMouseEvent *) override;

private:
    Ui::ItemBtnCon *ui;
};

#endif // ITEMBTNCON_H
