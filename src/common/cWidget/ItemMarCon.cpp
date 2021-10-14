#include "ItemMarCon.h"

ItemMarCon::ItemMarCon(QWidget *parent) : ItemBaseObj(parent)
{
    m_wBg = new QWidget(this);

    m_wBg->setObjectName("ItemMar_wBg");



    m_lb = new QLabel(m_wBg);

    m_lb->setObjectName("mar_lb");

    m_lb->setStyleSheet("border-color:rgba(0,0,0,0);");


    m_lb->setText("跑馬燈");

    m_lb->show();

    m_lb->adjustSize();

    startTimer(100);

}

void ItemMarCon::timerEvent(QTimerEvent *)
{



    if(m_obj==nullptr || m_listData.length()<=0)
        return;

    bool bHasWord = false;

    for(int i=0 ;i<m_listData.length();i++)
    {
        if(m_listData.at(i).length()>0)
        {
            bHasWord = true;
            break;
        }
    }

    if(!bHasWord)
        return;


    int iX = m_lb->x();

    if(iX>= -(m_lb->width()+20))
    {
        m_lb->move(iX-(3*m_iSpeed),0);

        m_lb->raise();
        // m_lb->move(iX-30,0);

    }
    else
    {

        m_iIdx++;

        if(m_iIdx>= m_listData.length())
            m_iIdx=0;

        setText(m_listData[m_iIdx]);


    }


}


void ItemMarCon::reSetSize()
{
    m_wBg->resize(size());

    m_lb->setMaximumHeight(height());

    m_lb->setMinimumHeight(height());

    //m_lb->resize(size());
}

void ItemMarCon::updateItem()
{
    if(m_obj == nullptr)
        return ;



    //return ;
    m_data = m_obj->m_data;

    m_listData = m_obj->m_data.value(Marquee::listText,QStringList()<<"跑馬燈").toStringList();

    m_iSpeed = m_obj->m_data.value(Marquee::speed,"3").toInt();



    QString sBg = getStyleSheetRgba(m_data.value(Label::bgColor,"#ffffffff").toString());

    QString sTxt = getStyleSheetRgba(m_data.value(Label::txtColor,"#000000ff").toString());

    QString sImagePath = m_data.value(Label::imagePath,"").toString().trimmed();


    if(sImagePath!="")
    {

        m_wBg->setStyleSheet("background-color:rgba(0,0,0,0);border-image:url("+sImagePath+");");

    }
    else
    {

        m_wBg->setStyleSheet("background-color:"+sBg);

    }

    m_lb->setStyleSheet("background-color:rgba(0,0,0,0);color:"+sTxt);

 //   m_lb->setStyleSheet("background-color:rgba(0,0,0,0);color:red");




    QFont f ;
    f.fromString("Arial,24,-1,5,50,0,0,0,0,0,Regular");

    QString sFont = m_data.value(Label::font,"Arial,24,-1,5,50,0,0,0,0,0,Regular").toString();

    if(sFont!="" && sFont.split(",").length()>5)
        f.fromString(sFont);

    f.setPixelSize(f.pixelSize()*m_diffSize);

#ifndef Q_OS_WINDOWS
    f.setPointSize(f.pointSize()*2.2);
#endif

    m_lb->setFont(f);

    qDebug()<<"update item : mar data";

    m_iIdx = 0;

    if(m_listData.length()>0)
        setText(m_listData[qBound(0,m_iIdx,m_listData.length()-1)]);
    else
        setText("");



}

void ItemMarCon::setText(QString st)
{

    m_lb->setText(st);

    m_lb->adjustSize();

    m_lb->setMaximumHeight(height());

    m_lb->setMinimumHeight(height());

    m_lb->move(width()+20,0);

}
