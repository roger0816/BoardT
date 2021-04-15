#ifndef ITEMMEDIACENT_H
#define ITEMMEDIACENT_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "ItemBase.h"
#include "Global.h"
#include "CPlayer.h"

class ItemMediaCent : public ItemBase
{
    Q_OBJECT
public:
    explicit ItemMediaCent(QWidget *parent = nullptr);

    ~ItemMediaCent();

    bool init() override;

    CPlayer *m_player;

private:

    QWidget *m_wBg;

    QStringList m_listVideo;

    QString m_sCurrentVideo;

    QWidget *m_wR;

    QWidget *m_wCent;

    QLabel *m_title;

    QWidget *m_wFunction;

    void reSize();

    QStringList m_listKey;

    QMap<QString,QStringList> m_dVideo;

    void showEvent(QShowEvent* ) override;

    void resizeEvent(QResizeEvent* ) override;

    void getConfig();

    void getVideo(QString sPath);

    QList<QPushButton*> m_listBtn;

    QPushButton *m_btnPlay;

    QPushButton *m_btnStop;

    QPushButton *m_btnNext;

    QPushButton *m_btnPre;

    int m_iTypeIdx = 0;

signals:

public slots:
    void playAndPause(bool b);

    void btnPre();

    void btnNext();

    void btnStop();


    void playing(QString sName);

    void videoClicked();
};

#endif // ITEMMEDIACENT_H
