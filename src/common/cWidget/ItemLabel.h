#ifndef ITEMLABEL_H
#define ITEMLABEL_H

#include <QWidget>
#include "ItemBaseObj.h"


namespace Ui {
class ItemLabel;
}

class ItemLabel : public ItemBaseObj
{
    Q_OBJECT

public:
    explicit ItemLabel(QWidget *parent = nullptr);
    ~ItemLabel();



    void updateItem();


private:
    Ui::ItemLabel *ui;

    DataText m_data;
};

#endif // ITEMLABEL_H
