#include "CPlayer.h"

#ifdef VLC

CPlayer::CPlayer(QWidget *parent) : QWidget(parent)
{
    vlcPlayer = nullptr;

    /* Initialize libVLC */
    vlcInstance = libvlc_new(0, NULL);

    /* Complain in case of broken installation */
    if (vlcInstance == NULL)
    {
        qDebug()<<"error vlc ";
    }

    m_listCache.append("0.0001");

    m_listCache.append("0.0002");

    //for test play
    //    QTimer::singleShot(1000,this,[=]
    //    {
    //            this->testPlay();
    //    });

    //   this->testPlay();

    startTimer(1000);
}

void CPlayer::setMute(bool mute)
{
    m_bIsMute = mute;

    if (vlcPlayer != NULL) {
        libvlc_audio_set_mute(vlcPlayer, m_bIsMute ? 1 : 0);
    }
}

CPlayer::~CPlayer()
{
    stop();

    if (vlcInstance)
        libvlc_release(vlcInstance);
}

void CPlayer::open(QString sPath)
{
   // sPath="rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mov";
    /* Stop if something is playing */
    if (vlcPlayer)// && libvlc_media_player_is_playing(vlcPlayer))
    {
        qDebug()<<"stop it and do open ";
        stop();
    }
    /* Create a new Media */

    libvlc_media_t *vlcMedia = libvlc_media_new_path(vlcInstance, qtu(sPath));
//     libvlc_media_t *vlcMedia = libvlc_media_new_location(vlcInstance, qtu(sPath));
    if (!vlcMedia)
        return;
    /* Create a new libvlc player */
    vlcPlayer = libvlc_media_player_new_from_media (vlcMedia);


    //  int  i = libvlc_video_get_track(vlcPlayer);



    /* Release the media */
    libvlc_media_release(vlcMedia);
    //    if(m_bFirst)
    //    {

    /* Integrate the video in the interface */
#if defined(Q_OS_MAC)
    libvlc_media_player_set_nsobject(vlcPlayer, (void *)videoWidget->winId());
#elif defined(Q_OS_UNIX)
    libvlc_media_player_set_xwindow(vlcPlayer, this->winId());
#elif defined(Q_OS_WIN)
    libvlc_media_player_set_hwnd(vlcPlayer, videoWidget->winId());
#endif
    //    }
    /* And start playback */
    //   libvlc_media_player_play (vlcPlayer);


    m_sCurrentFile = sPath;
    m_bFirst = false;
}

void CPlayer::openList(QStringList list)
{
    if(list.length()<=0)
        return ;

    m_listPlay = list;

    open(m_listPlay.at(0));

    play();
}

void CPlayer::play()
{
    qDebug()<<"play : ";

    if (!vlcPlayer)
        return;

    if (!libvlc_media_player_is_playing(vlcPlayer))
    {
        /* Play again */
           libvlc_audio_set_mute(vlcPlayer, m_bIsMute ? 1 : 0);

        libvlc_media_player_play(vlcPlayer);

    }

    emit playing(m_sCurrentFile);

    qDebug()<<libvlc_video_get_track(vlcPlayer);

}

void CPlayer::pause()
{


    if (!vlcPlayer)
        return;

    qDebug()<<"pause : ";

    if (libvlc_media_player_is_playing(vlcPlayer))
    {
        /* Pause */
        libvlc_media_player_pause(vlcPlayer);
    }

}

void CPlayer::stop()
{
    if(vlcPlayer)
    {
        /* stop the media player */
        libvlc_media_player_stop(vlcPlayer);

        /* release the media player */
        libvlc_media_player_release(vlcPlayer);

        /* Reset application values */
        vlcPlayer = nullptr;

    }
}

int CPlayer::changeVolume(int vol)
{
    if (vlcPlayer)
        return libvlc_audio_set_volume (vlcPlayer,vol);

    return 0;

}

void CPlayer::changePosition(int pos)
{
    if (vlcPlayer)
        libvlc_media_player_set_position(vlcPlayer, (float)pos/100.0);
}

void CPlayer::closeEvent(QCloseEvent *event)
{
    stop();
    event->accept();
}

void CPlayer::timerEvent(QTimerEvent *)
{

    if(m_listPlay.length()<1)
        return ;

    if(vlcPlayer)
    {

        if (libvlc_media_player_get_state(vlcPlayer) == libvlc_Ended)
        {
            stop();

            m_iIdx++;

            if(m_iIdx>=m_listPlay.length())
                m_iIdx = 0;

            open(m_listPlay.at(m_iIdx));

            play();
        }

    }
}

void CPlayer::setPlayAdnPause(bool bPlay)
{
    if(bPlay)
        play();
    else
        pause();
}

void CPlayer::testPlay()
{

    open("/home/pi/work/Test01/res/video/video.mp4");

    play();
}

#else

CPlayer::CPlayer(QWidget *parent):QWidget(parent)
{
    m_player = new QMediaPlayer;

    m_playList = new QMediaPlaylist;

    m_videoWidget = new QVideoWidget;

    m_player->setVideoOutput(m_videoWidget);

    //  m_videoWidget->setGeometry(0,0,640,480);

    // m_videoWidget->setParent(this);


    m_videoWidget->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    m_videoWidget->setWindowOpacity(1);


    m_videoWidget->show();

    m_videoWidget->hide();



}

CPlayer::~CPlayer()
{
    qDebug()<<"de cPlayer";
}

void CPlayer::open(QString file)
{

    emit playing(file);

    m_player->setMedia(QUrl::fromLocalFile(file));

    m_player->play();
}

void CPlayer::openList(QStringList list)
{

    m_playList->clear();

    foreach(QString st ,list)
    {
        m_playList->addMedia(QUrl(st));
    }

    m_player->setPlaylist(m_playList);

    if(list.length()>0)
        m_playList->setCurrentIndex(1);

    m_player->play();

}

void CPlayer::play()
{
    m_player->play();
}

void CPlayer::pause()
{
    m_player->pause();
}

void CPlayer::stop()
{
    m_player->stop();
}

int CPlayer::changeVolume(int val)
{
    m_player->setVolume(val);
    return val;
}

void CPlayer::changePosition(int)
{

}

void CPlayer::showEvent(QShowEvent *)
{
    m_videoWidget->resize(size());
}

void CPlayer::setPlayAdnPause(bool)
{
    m_videoWidget->resize(size());
}

void CPlayer::testPlay()
{

}


#endif
