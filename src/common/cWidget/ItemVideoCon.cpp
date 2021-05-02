#include "ItemVideoCon.h"

ItemVideoCon::ItemVideoCon(QWidget *parent) : ItemBaseObj(parent)
{
    m_wBg = new QWidget(this);

    m_wBg->setObjectName("m_wBg");

    m_wBg->setStyleSheet("QWidget#m_wBg{background-color:black;}");

    m_player = new CPlayer(m_wBg);

    m_player->setStyleSheet("background-color:rgb(177,177,177);");


}

ItemVideoCon::~ItemVideoCon()
{
    m_player->stop();
}

void ItemVideoCon::updateItem()
{
    if(m_obj ==nullptr)
    {
        return ;
    }

    m_player->stop();

    m_player->openList(m_obj->m_dataVideo.listName);
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
    m_player->resize(m_wBg->size());
}
