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
    ItemLabel::updateItem();

    m_iReadSpeed = m_obj->m_data.value(TxtValue::readSpeed,2).toInt();

    m_iPlaySpeed = m_obj->m_data.value(TxtValue::playSpeed,5).toInt();

    m_iSelect = m_obj->m_data.value(TxtValue::index,0).toInt();

    m_iLimitMin = m_obj->m_data.value(TxtValue::min,0).toInt();

    m_iLimitMax = m_obj->m_data.value(TxtValue::max,99).toInt();

    m_sMsg1 = m_obj->m_data.value(TxtValue::minMsg,"").toString();

    m_sMsg2 = m_obj->m_data.value(TxtValue::maxMsg,"").toString();


    m_lb->setText(m_data.value(Label::text,"Txt文字").toString());


}


void ItemTxObjCon::doRead()
{

    qDebug()<<"do read ";

    //  QFile f(QApplication::applicationDirPath()+"/input.txt");
    QFile *file = new QFile(QApplication::applicationDirPath()+"/input.txt");

    if(file->open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QString st = file->readAll();

          qDebug()<<"readall : "<<st;
        QStringList list  = st.split(",");

        qDebug()<<"iselect : "<<m_iSelect<<" listlen : "<<list.length();

        if( m_iSelect >=0  && list.length()>0 &&  m_iSelect < list.length() )
        {

            m_sCurrentValue = list.at(m_iSelect);

            qDebug()<<"all value : "<<list<<"  ,  current value : "<<m_sCurrentValue;
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

    if(m_sCurrentValue.toInt() <= m_iLimitMin)
    {

        m_sCurrentMsg = m_sMsg1;
    }

    if(m_sCurrentValue.toInt() > m_iLimitMax)
    {


        m_sCurrentMsg = m_sMsg2;
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

        qDebug()<<"timer : " <<m_iSec  ;

    if(m_iSec%m_iReadSpeed==0)
    {
        doRead();
    }

    if(m_iSec%m_iPlaySpeed==0)
    {

        doChangeShow();

    }
}
