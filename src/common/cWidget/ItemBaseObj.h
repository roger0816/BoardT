#ifndef ITEMBASEOBJ_H
#define ITEMBASEOBJ_H

#include <QWidget>
#include <Voj.h>
#include <QFont>
//#include "ObjData.h"

#include "cData/ObjData.h"
#include "cData/CData.h"


class ItemBaseObj : public QWidget
{
    Q_OBJECT
public:
    explicit ItemBaseObj(QWidget *parent = nullptr);

    void setData(ObjData *obj);

    virtual void init(){}

    virtual void updateItem(){}

    void resizeEvent(QResizeEvent *) override{reSetSize();}

    void showEvent(QShowEvent *) override{reSetSize();}

    virtual void reSetSize(){}


    float m_diffSize = 1.000;

    ObjData* m_obj =nullptr;

    QMap<QString,QVariant> m_data;

signals:

};

#endif // ITEMBASEOBJ_H
