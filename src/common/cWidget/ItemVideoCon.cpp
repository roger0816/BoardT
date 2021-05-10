#include "ItemVideoCon.h"

ItemVideoCon::ItemVideoCon(QWidget *parent) : ItemBaseObj(parent)
{
    m_wBg = new QWidget(this);

    m_wBg->setObjectName("m_wVideoBg");

    m_wBg->setStyleSheet("QWidget#m_wVideoBg{background-color:black;}");



}

ItemVideoCon::~ItemVideoCon()
{

}



void ItemVideoCon::updateItem()
{
    m_listRes = m_obj->m_dataVideo.listName;
}

void ItemVideoCon::resizeEvent(QResizeEvent *)
{
    reSize();
}

void ItemVideoCon::showEvent(QShowEvent *)
{
    reSize();
}



void ItemVideoCon::reSize()
{

    m_wBg->resize(size());

}
