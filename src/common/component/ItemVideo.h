#ifndef ITEMVIDEO_H
#define ITEMVIDEO_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "ItemBase.h"
#include "Global.h"
#include "CPlayer.h"

class ItemVideo : public ItemBase
{
    Q_OBJECT
public:
    explicit ItemVideo(QWidget *parent = nullptr);

    ~ItemVideo();

    bool init() override;

    CPlayer *m_player;

    void setPlayList(QStringList list);

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

#endif // ITEMVIDEO_H
