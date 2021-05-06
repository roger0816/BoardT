#include "ItemMarCon.h"

ItemMarCon::ItemMarCon(QWidget *parent) : ItemBaseObj(parent)
{
    m_wBg = new QWidget(this);

    m_wBg->setObjectName("ItemMar_wBg");
}

void ItemMarCon::timerEvent(QTimerEvent *)
{

}

void ItemMarCon::resizeEvent(QResizeEvent *)
{
    reSetSize();
}

void ItemMarCon::showEvent(QShowEvent *)
{
    reSetSize();
}

void ItemMarCon::reSetSize()
{
    m_wBg->resize(size());
}
