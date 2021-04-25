#include "ItemContent.h"
#include "ui_ItemContent.h"

ItemContent::ItemContent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemContent)
{
    ui->setupUi(this);

    this->setObjectName("ItemContent_");

    ui->wBg->setObjectName("itemContent_bg");

    m_Bg = ui->wBg;

    lb = ui->label;
}

ItemContent::~ItemContent()
{
    delete ui;
}

void ItemContent::setRoll(bool b)
{
    m_bRoll = b;

    if(m_bRoll)
    emit sendFocus();

    updateBg();

    return ;




}

bool ItemContent::getRoll()
{
    return m_bRoll;
}

void ItemContent::setBg(QString sPngPath)
{

    m_sBgPash = sPngPath;

//    setRoll(m_bRoll);

    updateBg();


}

void ItemContent::setBgColor(QColor color)
{

    m_bgColor = color;

      updateBg();
  //  setRoll(m_bRoll);
}

void ItemContent::mousePressEvent(QMouseEvent *e)
{
    m_bMove = false;

    setRoll(true);

    if(e->x()>width()-10 && e->y() > height()-10)
    {
        m_bChangeSize = true;
    }
    else
    {
        m_bChangeSize = false;
    }

    m_preP = e->pos();

    m_preSize = size();
}

void ItemContent::mouseReleaseEvent(QMouseEvent *e)
{
    if(m_bMove)
    emit sendUpdate();
}

void ItemContent::mouseMoveEvent(QMouseEvent *e)
{
    m_bMove = true;

    QPoint move = e->pos()-m_preP;

    QPoint af = this->pos()+move;

    if(!m_bChangeSize)
    {
        this->move(af);
    }
    else
    {

        QSize t(m_preSize+QSize(move.x(),move.y()));
        int iW = qBound(40,t.width(),this->parentWidget()->width()+10);

        int iH = qBound(40,t.height(),this->parentWidget()->height()+10);

        resize(iW,iH);
    }

}

void ItemContent::updateBg()
{
    QString sStyle;

    QString sArg =" border-image:url("+m_sBgPash+");";


    //  QString sArg ="border-image:url(C:/Users/chenchaowei/Documents/work/BoardT/bin/dataB/layerBK/model0/14_2/10-2.png);";

    if(m_bRoll)
    {
        sStyle = "QWidget#"+ui->wBg->objectName()+"{%1 border: 2px groove blue; border-style: outset;}";


        if(m_sBgPash=="")
        {

            QString sColor="background-color:  rgba(%1,%2,%3,%4);";

            sArg = sColor.arg(m_bgColor.red()).arg(m_bgColor.green()).arg(m_bgColor.blue()).arg(m_bgColor.alpha());


        }



    }
    else
    {

        sStyle = "QWidget#"+ui->wBg->objectName()+"{border: 1px groove gray; border-style: outset;%1}";


        if(m_sBgPash=="")
        {
            QString sColor="background-color:  rgba(%1,%2,%3,%4);";

            sArg = sColor.arg(m_bgColor.red()).arg(m_bgColor.green()).arg(m_bgColor.blue()).arg(m_bgColor.alpha());

        }



    }
    if(m_sBgPash!="")
        qDebug()<<"BB: "<<sStyle.arg(sArg);
    ui->wBg->setStyleSheet(sStyle.arg(sArg));
}
