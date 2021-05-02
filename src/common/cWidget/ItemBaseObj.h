#ifndef ITEMBASEOBJ_H
#define ITEMBASEOBJ_H

#include <QWidget>
#include <Voj.h>
#include <QFont>
#include "ObjData.h"


class ItemBaseObj : public QWidget
{
    Q_OBJECT
public:
    explicit ItemBaseObj(QWidget *parent = nullptr);

    void setData(ObjData *obj);

    virtual void updateItem(){}

    float m_diffSize = 1.000;

    ObjData* m_obj =nullptr;

signals:

};

#endif // ITEMBASEOBJ_H
