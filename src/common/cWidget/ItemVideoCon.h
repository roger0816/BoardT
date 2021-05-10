#ifndef ITEMVIDEOCON_H
#define ITEMVIDEOCON_H

#include <QObject>
#include <QWidget>
#include "CPlayer.h"
#include "ItemBaseObj.h"
#include <QShowEvent>
#include <QResizeEvent>

class ItemVideoCon : public ItemBaseObj
{
    Q_OBJECT
public:
    explicit ItemVideoCon(QWidget *parent = nullptr);
    ~ItemVideoCon();

     void init() override;

private:

    CPlayer *m_player;

    void resizeEvent(QResizeEvent *) override;

    void showEvent(QShowEvent* ) override;

    void setPlayList(QStringList list);

    void reSize();

    QWidget *m_wBg;


signals:

};

#endif // ITEMVIDEOCON_H
