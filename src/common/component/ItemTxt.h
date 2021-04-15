#ifndef ITEMTXT_H
#define ITEMTXT_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include "ItemBase.h"
#include "Global.h"

class ItemTxt : public ItemBase
{
    Q_OBJECT
public:
    explicit ItemTxt(QWidget *parent = nullptr);

    bool init() override;

    QStringList m_listTxt;

    QWidget *m_wBg;

    QLabel *m_lb;

    void showEvent(QShowEvent *) override;

    bool m_bMarquee=false;

    QStringList getFileData(QByteArray dData);



    QPropertyAnimation *m_ani;

    int m_iIdx=0;


private slots:
       void startMarquee();

       void aniFinished();

signals:

};

#endif // ITEMTXT_H
