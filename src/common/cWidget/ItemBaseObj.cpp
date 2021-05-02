#include "ItemBaseObj.h"

ItemBaseObj::ItemBaseObj(QWidget *parent) : QWidget(parent)
{

}

void ItemBaseObj::setData(ObjData *obj)
{
    m_obj = obj;

    updateItem();
}
