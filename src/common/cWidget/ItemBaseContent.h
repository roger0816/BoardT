#ifndef ITEMBASECONTENT_H
#define ITEMBASECONTENT_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include "ObjData.h"
#include "CData.h"
#include <QMouseEvent>
#include "ItemLabel.h"
#include "QGridLayout"
#include <QResizeEvent>
#include "ItemPicCon.h"
#include "ItemVideoCon.h"

namespace Ui {
class ItemBaseContent;
}



class ItemEditTouch :public QWidget
{
    Q_OBJECT
public:
    explicit ItemEditTouch(QWidget *parent = nullptr):QWidget(parent)
    {
        m_wBg = new QWidget(this);

        m_wBg->resize(20,20);

        m_wBg->setObjectName("m_touch_wBg");

        m_lb = new QLabel(m_wBg);

        QFont f;

        f.setBold(true);

        f.setWeight(QFont::Black);

        f.setPixelSize(10);

        m_lb->setFont(f);

        m_lb->resize(15,15);

        m_lb->setText("◢");



//        QHBoxLayout * lay=  new QHBoxLayout(this);

//        lay->setMargin(0);

//        lay->setSpacing(0);

//        lay->addWidget(m_wBg);

//        setLayout(lay);

        setRoll(false);
    }

    void setRoll(bool b)
    {

        QString sStyle;


        if(b)
        {
            sStyle = "QWidget#%1{border: 2px groove blue; border-style: outset;}";


        }
        else
        {

            sStyle = "QWidget#%1{border: 1px groove gray; border-style: outset;}";


        }

        setStyleSheet(sStyle.arg(m_wBg->objectName()));
    }

private:
    void mousePressEvent(QMouseEvent *e)  override{emit sendMouse(e);}

    void mouseReleaseEvent(QMouseEvent *e ) override{emit sendMouse(e);}

    void mouseMoveEvent(QMouseEvent *e) override{emit sendMouse(e);}

    void resizeEvent(QResizeEvent *) override
    {
        m_wBg->resize(size());

        m_lb->move(width()-m_lb->width()-2,height()-m_lb->height()-2);
    }

    QWidget *m_wBg;

    QLabel *m_lb;

signals:
    void sendMouse(QMouseEvent *);

};

class ItemBaseContent : public QWidget
{
    Q_OBJECT

public:
    explicit ItemBaseContent(QWidget *parent = nullptr);
    ~ItemBaseContent();

    void setData(ObjData *obj,float diffSize = 1.000);

    void updateItem();

    void setRoll(bool b);

    void setEdit(bool b);

    QString m_sPath;

    QString m_sModelName;

    QString m_sLayerName;

    QString m_sName;

    QString m_sType;

    float m_diffSize = 1.000;


    QWidget *m_wBg;

    ItemBaseObj *itemLabel = nullptr;


    ObjData *m_obj = nullptr;

signals:

    void sendFocus();

    void sendUpdate();
private:
    Ui::ItemBaseContent *ui;

    QGridLayout *m_lay;

    ItemEditTouch *m_touch;

    bool m_bEdit = false;


    void resizeEvent(QResizeEvent *) override;

    void slotMouseEvent(QMouseEvent *e);

    bool m_bRoll = true;

    bool m_bMove = false;

    QPoint m_preP;

    QSize m_preSize;

    bool m_bChangeSize = false;

    QString m_sBgPash="";

    QColor m_bgColor=QColor(255,255,255,255);





};

#endif // ITEMBASECONTENT_H
