#include "ItemDateTime.h"


ItemDateTime::ItemDateTime(QWidget *parent) :
    ItemLabel(parent)
{
    m_lb->setText(QDateTime::currentDateTime().toString("yyyy/MM/dd"));

    startTimer(1000);
}

ItemDateTime::~ItemDateTime()
{

}

void ItemDateTime::setString(QString sDate, QString sTime)
{
    m_sDate = sDate;

    m_sTime = sTime;
}

void ItemDateTime::updateItem()
{
    if(m_obj == nullptr)
        return ;

    m_data = m_obj->m_data;

    m_sDate = m_obj->m_data[DateTime::dateStr].toString();

    m_sTime = m_obj->m_data[DateTime::timeStr].toString();

    m_iChangeTime = m_obj->m_data[DateTime::speed].toInt();


    setLbStyle(Label::txtColor,Label::bgColor,Label::imagePath,Label::font,Label::alignCenter);

    m_lb->setAlignment(Qt::AlignCenter);

    change();
}

void ItemDateTime::timerEvent(QTimerEvent *)
{

    m_iSec++;

    if(m_iSec%m_iChangeTime==0)
    {
        change();
    }

}

void ItemDateTime::change()
{

    if(m_bCurrentShowDate)
    {
        m_lb->setText(QDateTime::currentDateTime().toString(m_sDate));
    }
    else
    {
        m_lb->setText(QDateTime::currentDateTime().toString(m_sTime));
    }

    m_bCurrentShowDate = !m_bCurrentShowDate;
}
