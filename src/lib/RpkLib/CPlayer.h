#ifndef CPLAYER_H
#define CPLAYER_H

#include <QWidget>

#include <QDebug>


#include <QCloseEvent>
#include <QTimer>
#include <QPalette>
#include <QTimerEvent>


#ifdef VLC
#include <vlc/vlc.h>

#define qtu( i ) ((i).toUtf8().constData())

class CPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit CPlayer(QWidget *parent = nullptr);

    ~CPlayer();
    
    void setShowWidget(QWidget *w);

    void open(QString sPath);

    void openList(QStringList list);

    void play();

    void pause();

    void stop();

    void setMute(bool mute);


    int changeVolume(int vol);

    void changePosition(int pos);

    QString m_sCurrentFile;

    bool m_bIsMute = false;
private:

    libvlc_instance_t *vlcInstance;

    libvlc_media_player_t *vlcPlayer = nullptr;

    virtual void closeEvent(QCloseEvent*);

    QStringList m_listPlay;

    int m_iIdx = 0;

    void timerEvent(QTimerEvent *) override;

    QStringList m_listCache;

    bool m_bFirst = true;
    
    QWidget * m_showWidget;   

signals:
    void playing(QString sName);

public slots:

    void setPlayAdnPause(bool bPlay);

    void testPlay();
};

#else

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>
#include <QVBoxLayout>
#include <QDebug>

class CPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit CPlayer(QWidget *parent = nullptr);

    ~CPlayer();

    void open(QString file);

    void openList(QStringList list);

    void setMute(bool mute){}

    void play();

    void pause();

    void stop();

    int changeVolume(int val);

    void changePosition(int );

    void showEvent(QShowEvent *) override;

    QString m_sCurrentFile;


signals:
    void playing(QString sName);

public slots:

    void setPlayAdnPause(bool );

    void testPlay();

private:

    QMediaPlayer *m_player;

    QVideoWidget *m_videoWidget;

    QMediaPlaylist *m_playList;


};

#endif

#endif // CPLAYER_H
