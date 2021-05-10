#include "ItemMarCon.h"

ItemMarCon::ItemMarCon(QWidget *parent) : ItemBaseObj(parent)
{
    m_wBg = new QWidget(this);

    m_wBg->setObjectName("ItemMar_wBg");


//    m_wBg->setStyleSheet("");

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




    int iX = m_lb->x();

    if(iX>= -(m_lb->width()+20))
    {
        m_lb->move(iX-(3*m_iSpeed),0);

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

    qDebug()<<"update item : mar";

    if(m_obj->m_dataMar.listText.length()<=0)
        return ;

    QColor bgColor = m_obj->m_dataText.bgColor;

    QColor txtColor = m_obj->m_dataText.textColor;


    QString sStyle = "color:rgba(%1,%2,%3,%4);"
                     "background-color:rgba(%5,%6,%7,%8);border-color:rgba(0,0,0,0);";


    DataText m_data = m_obj->m_dataText;;

    if(m_data.m_sImagePath.trimmed()!="")
    {
        m_lb->setStyleSheet(sStyle.arg(m_data.textColor.red())
                                 .arg(m_data.textColor.green())
                                 .arg(m_data.textColor.blue())
                                 .arg(m_data.textColor.alpha())
                                 .arg(0)
                                 .arg(0)
                                 .arg(0)
                                 .arg(0)
                                // +" border-image:url("+m_data.m_sImagePath
                                    +");");

        m_wBg->setStyleSheet(sStyle.arg(m_data.textColor.red())
                                 .arg(m_data.textColor.green())
                                 .arg(m_data.textColor.blue())
                                 .arg(m_data.textColor.alpha())
                                 .arg(0)
                                 .arg(0)
                                 .arg(0)
                                 .arg(0)
                                 +" border-image:url("+m_data.m_sImagePath+");");


    }
    else
    {
    m_lb->setStyleSheet(sStyle.arg(m_data.textColor.red())
                      .arg(m_data.textColor.green())
                      .arg(m_data.textColor.blue())
                      .arg(m_data.textColor.alpha())
                      .arg(m_data.bgColor.red())
                      .arg(m_data.bgColor.green())
                      .arg(m_data.bgColor.blue())
                      .arg(0)
                        );


    m_wBg->setStyleSheet(sStyle.arg(m_data.textColor.red())
                      .arg(m_data.textColor.green())
                      .arg(m_data.textColor.blue())
                      .arg(m_data.textColor.alpha())
                      .arg(m_data.bgColor.red())
                      .arg(m_data.bgColor.green())
                      .arg(m_data.bgColor.blue())
                      .arg(m_data.bgColor.alpha())
                        );
    }

    QFont f = m_data.font;

    f.setPixelSize(f.pixelSize()*m_diffSize);

    m_lb->setFont(f);

//    m_lb->setText(m_data.sText);

    if(m_data.bIsCent)
        m_lb->setAlignment(Qt::AlignCenter);
    else
        m_lb->setAlignment(Qt::AlignLeading);



    qDebug()<<"update item : mar data";

    m_iSpeed = m_obj->m_dataMar.iSpeed;

    m_listData = m_obj->m_dataMar.listText;

    m_iIdx = 0;

    setText(m_listData[m_iIdx]);



}

void ItemMarCon::setText(QString st)
{

    m_lb->setText(st);

    m_lb->adjustSize();

    m_lb->setMaximumHeight(height());

    m_lb->setMinimumHeight(height());

    m_lb->move(width()+20,0);

}
