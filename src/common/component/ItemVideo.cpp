#include "ItemVideo.h"

ItemVideo::ItemVideo(QWidget *parent) : ItemBase(parent)
{

    m_wBg = new QWidget(this);

    m_wBg->setObjectName("m_wBg");

    m_wBg->setStyleSheet("QWidget#m_wBg{background-color:black;}");

    m_player = new CPlayer(m_wBg);

    m_player->connect(m_player,&CPlayer::playing,this,&ItemVideo::playing);

    m_player->setStyleSheet("background-color:rgb(177,177,177);");


   // connect(&Global::Instance(),&Global::callPlay,m_player,&CPlayer::setPlayAdnPause);
}

ItemVideo::~ItemVideo()
{
    m_player->stop();
}

bool ItemVideo::init()
{

   // m_player->openList(QStringList()<<"/home/pi/BoardT/bin/video/a.mp4");


   // getVideo(m_sPath+"/../../../video");


    QStringList list = QDir(m_sPath).entryList(QStringList()<<"*.mp4");


    m_listVideo.clear();

    for(int i=0;i<list.length();i++)
    {
        m_listVideo.append(m_sPath+"/"+list.at(i));
    }


    m_player->openList(m_listVideo);


    return true;
}

void ItemVideo::setPlayList(QStringList list)
{
    m_listVideo = list;

    m_player->openList(m_listVideo);

}

void ItemVideo::reSize()
{
    m_wBg->resize(size());
    m_player->resize(m_wBg->size());
}

void ItemVideo::showEvent(QShowEvent *)
{
    reSize();


}

void ItemVideo::resizeEvent(QResizeEvent *)
{
    reSize();
}



void ItemVideo::getVideo(QString sPath)
{
    QStringList listDir = QDir(sPath).entryList(QDir::Dirs);



}

void ItemVideo::playing(QString sName)
{
    Q_UNUSED(sName);
}

void ItemVideo::setPlayAdnPause(bool bPlay)
{

    qDebug()<<"  BBB  "<<bPlay;

    if(bPlay)
        m_player->play();
    else {
        m_player->pause();
    }
}


