#ifndef ITEMLABEL_H
#define ITEMLABEL_H

#include <QWidget>
#include <Voj.h>
#include <QFont>
#include "ObjData.h"

namespace Ui {
class ItemLabel;
}

class ItemLabel : public QWidget
{
    Q_OBJECT

public:
    explicit ItemLabel(QWidget *parent = nullptr);
    ~ItemLabel();


    void setData(ObjData *obj);

    void updateItem();

    float m_diffSize = 1.000;

    ObjData* m_obj =nullptr;

private:
    Ui::ItemLabel *ui;

    DataText m_data;
};

#endif // ITEMLABEL_H
