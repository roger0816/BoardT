#ifndef ITEMCONTENT_H
#define ITEMCONTENT_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QLabel>
#include "VojData.h"

namespace Ui {
class ItemContent;
}

class ItemContent : public QWidget
{
    Q_OBJECT

public:
    explicit ItemContent(QWidget *parent = nullptr);
    ~ItemContent();

    void setRoll(bool b);

    bool getRoll();

    void setBg(QString sPngPath);

    void setBgColor(QColor color);

    QWidget *m_Bg;

    QLabel *lb;

    QString m_sName;

    int m_iType;

    DataText m_dataText;

    QRect origiRect;

signals:

   // void sendPos(int x,int y,int w,int h);

    void sendFocus();

    void sendUpdate();

private:
    Ui::ItemContent *ui;

    void mousePressEvent(QMouseEvent *e)  override;

    void mouseReleaseEvent(QMouseEvent *e ) override;

    void mouseMoveEvent(QMouseEvent *e) override;

    bool m_bRoll = true;

    QPoint m_preP;

    QSize m_preSize;

    bool m_bChangeSize = false;

    QString m_sBgPash="";

    QColor m_bgColor=QColor(255,255,255,255);

    void updateBg();


};

#endif // ITEMCONTENT_H
