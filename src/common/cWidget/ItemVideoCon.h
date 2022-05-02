#ifndef ITEMVIDEOCON_H
#define ITEMVIDEOCON_H

#include <QObject>
#include <QWidget>
#include "CPlayer.h"
#include "ItemBaseObj.h"
#include <QShowEvent>
#include <QResizeEvent>
#include <QLabel>



class ItemPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit ItemPlayer(QWidget *parent = nullptr);

    ~ItemPlayer();

    CPlayer *m_player;

    void setPlayList(QStringList list);

    void setMute(bool bMute);
    
#ifdef VLC
    void setCPlayer(CPlayer* player);
#endif    

private:

    QWidget *m_wBg;

    QStringList m_listVideo;

    void reSize();

    void showEvent(QShowEvent* ) override;

    void resizeEvent(QResizeEvent* ) override;

    void getVideo(QString sPath);
public slots:
    void playing(QString sName);

    void setPlayAdnPause(bool bPlay);

};


class ItemVideoCon : public ItemBaseObj
{
    Q_OBJECT
public:
    explicit ItemVideoCon(QWidget *parent = nullptr);
    ~ItemVideoCon();

     void updateItem() override;

    QStringList m_listRes;


private:


    void resizeEvent(QResizeEvent *) override;

    void showEvent(QShowEvent* ) override;

    void setPlayList(QStringList list);

    void reSize();

    QLabel *m_wBg;


signals:

};

#endif // ITEMVIDEOCON_H
