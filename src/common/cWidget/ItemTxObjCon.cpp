#include "ItemTxObjCon.h"

ItemTxObjCon::ItemTxObjCon(QWidget *parent) : ItemLabel(parent)
{
    m_file.setFileName(QApplication::applicationDirPath()+"/input.txt");

    // startTimer(1000);

    connect(&m_timer,&QTimer::timeout,this,&ItemTxObjCon::slotTimer);

    m_timer.start(1000);


}

void ItemTxObjCon::timerEvent(QTimerEvent *)
{



}

void ItemTxObjCon::updateItem()
{
   // ItemLabel::updateItem();

    if(m_obj!=nullptr)
        m_data = m_obj->m_data;


    m_iReadSpeed = m_obj->m_data.value(TxtValue::readSpeed,2).toInt();

    m_iPlaySpeed = m_obj->m_data.value(TxtValue::playSpeed,5).toInt();

    m_iSelect = m_obj->m_data.value(TxtValue::index,0).toInt();

    m_iLimitMin = m_obj->m_data.value(TxtValue::min,0).toDouble();

    m_iLimitMax = m_obj->m_data.value(TxtValue::max,99).toDouble();

    QStringList listText = m_obj->m_data.value(TxtValue::msg,"").toStringList();

    while(listText.length()<3)
    {
        listText.append("");
    }

    m_sMsgMin = listText.first();

    m_sMsgMax = listText.last();

    m_sMsg = listText.at(1);

    m_lb->setText(m_data.value(Label::text,"Txt文字").toString());

    QColor bgColor = m_data.value(Label::bgColor,"#ffffffff").toString();
    //bgColor.name(QColor::HexArgb)


    QColor txtColor = m_data.value(Label::txtColor,"#ff000000").toString();



}


void ItemTxObjCon::doRead()
{


    //  QFile f(QApplication::applicationDirPath()+"/input.txt");
    QFile *file = new QFile(QApplication::applicationDirPath()+"/input.txt");

    if(file->open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QString st = file->readAll();


        QStringList list  = st.split(",");


        if( m_iSelect >=0  && list.length()>0 &&  m_iSelect < list.length() )
        {

            m_sCurrentValue = list.at(m_iSelect);

        }
        file->close();
    }

    delete file;


}

void ItemTxObjCon::doChangeShow()
{


    if(m_sCurrentValue=="" || m_sCurrentValue.toInt() <0 )
        return ;
    m_sCurrentMsg="";

    qDebug()<<"current : "<<m_sCurrentValue.toDouble()<<" , "<<m_iLimitMin<<" , "<<m_iLimitMax;

    if(m_sCurrentValue.toDouble() < m_iLimitMin)
    {

        m_sCurrentMsg = m_sMsgMin;
    }

    else if(m_sCurrentValue.toDouble() > m_iLimitMax)
    {

        m_sCurrentMsg = m_sMsgMax;
    }
    else
    {
        m_sCurrentMsg = m_sMsg;
    }

    QString sDisplay = m_sCurrentValue;

    if(m_bIsShowValue && m_sCurrentMsg!="")
    {

        sDisplay = m_sCurrentMsg;
    }

    m_bIsShowValue = !m_bIsShowValue;

    m_lb->setText(sDisplay);
}

void ItemTxObjCon::slotTimer()
{


    m_iSec++;

    if(m_iSec>=10000)
        m_iSec=1;

    if(m_iReadSpeed<2)
        m_iReadSpeed = 2;

    if(m_iPlaySpeed <4)
        m_iPlaySpeed = 4;


    if(m_iSec%m_iReadSpeed==0)
    {
        doRead();
    }

    if(m_iSec%m_iPlaySpeed==0)
    {

        doChangeShow();

    }
}
