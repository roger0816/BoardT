#ifndef ITEMBTNCON_H
#define ITEMBTNCON_H

#include <QWidget>
#include "ItemBaseObj.h"
namespace Ui {
class ItemBtnCon;
}

class ItemBtnCon : public ItemBaseObj
{
    Q_OBJECT

public:
    explicit ItemBtnCon(QWidget *parent = nullptr);

    void init() override;

    void updateItem() override;
    ~ItemBtnCon();

private:
    Ui::ItemBtnCon *ui;
};

#endif // ITEMBTNCON_H
