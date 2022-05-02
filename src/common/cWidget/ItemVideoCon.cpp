#include "ItemVideoCon.h"



ItemPlayer::ItemPlayer(QWidget *parent) : QWidget(parent)
{

    m_wBg = new QWidget(this);

    m_wBg->setObjectName("m_wBg");

    m_wBg->setStyleSheet("QWidget#m_wBg{background-color:black;}");
    
#ifndef VLC    
    
    m_player = new CPlayer(m_wBg);

    m_player->connect(m_player,&CPlayer::playing,this,&ItemPlayer::playing);

    m_player->setStyleSheet("background-color:rgb(177,177,177);");
#endif

   // connect(&Global::Instance(),&Global::callPlay,m_player,&CPlayer::setPlayAdnPause);
}

ItemPlayer::~ItemPlayer()
{
    m_player->stop();
}


void ItemPlayer::setPlayList(QStringList list)
{
    m_listVideo = list;

    m_player->openList(m_listVideo);

}

void ItemPlayer::setMute(bool bMute)
{
    m_player->setMute(bMute);
}

#ifdef VLC
void ItemPlayer::setCPlayer(CPlayer *player)
{
    m_player = player;

    m_player->setShowWidget(this);

    m_player->connect(m_player,&CPlayer::playing,this,&ItemPlayer::playing);

    m_player->setStyleSheet("background-color:rgb(177,177,177);");
}
#endif

void ItemPlayer::reSize()
{
    m_wBg->resize(size());
    m_player->resize(m_wBg->size());
}

void ItemPlayer::showEvent(QShowEvent *)
{
    reSize();


}

void ItemPlayer::resizeEvent(QResizeEvent *)
{
    reSize();
}



void ItemPlayer::getVideo(QString sPath)
{
    QStringList listDir = QDir(sPath).entryList(QDir::Dirs);



}

void ItemPlayer::playing(QString sName)
{
    Q_UNUSED(sName);
}

void ItemPlayer::setPlayAdnPause(bool bPlay)
{


    if(bPlay)
        m_player->play();
    else {
        m_player->pause();
    }
}




ItemVideoCon::ItemVideoCon(QWidget *parent) : ItemBaseObj(parent)
{
    m_wBg = new QLabel(this);

    m_wBg->setObjectName("m_wVideoBg");

  //  m_wBg->setStyleSheet("QWidget#m_wVideoBg{background-color:black;color:white;}");

     m_wBg->setStyleSheet("QWidget#m_wVideoBg{background-color:gray;color:white;}");

    m_wBg->setAlignment(Qt::AlignHCenter);

    m_wBg->setText("VIDEO");


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
