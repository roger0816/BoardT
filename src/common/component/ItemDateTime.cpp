#include "ItemDateTime.h"

ItemDateTime::ItemDateTime(QWidget *parent) : ItemBase(parent)
{

    m_wBg = new QWidget(this);

    QVBoxLayout *lay0 = new QVBoxLayout;

    lay0->setMargin(0);

    lay0->addWidget(m_wBg);

    setLayout(lay0);

    m_lb0 =new QLabel(m_wBg);


    m_lb1 = new QLabel(m_wBg);

    QVBoxLayout *lay = new QVBoxLayout;

    lay->addWidget(m_lb0);

    lay->addWidget(m_lb1);

    m_wBg->setLayout(lay);



}

bool ItemDateTime::init()
{


    m_wBg->setStyleSheet("background-color:"+Global::Instance().decodeColor(config("Base/bgColor").toString())+";");

    QFont f;

    f.setPixelSize(config("Date/txtSize").toInt()*Global::Instance().m_fDiffSize);

    m_lb0->setFont(f);

    m_lb0->setStyleSheet("color:"+Global::Instance().decodeColor(config("Date/txtColor").toString())+";"+
                        "background-color:rgba(0,0,0,0);");


    if(config("Date/alignCenter").toBool())
        m_lb0->setAlignment(Qt::AlignCenter);

    QFont f1;

    f1.setPixelSize(config("Time/txtSize").toInt()*Global::Instance().m_fDiffSize);

    m_lb1->setFont(f1);

    m_lb1->setStyleSheet("color:"+Global::Instance().decodeColor(config("Time/txtColor").toString())+";"+
                        "background-color:rgba(0,0,0,0);");


    if(config("Time/alignCenter").toBool())
        m_lb1->setAlignment(Qt::AlignCenter);

    startTimer(1000);


    return true;
}

void ItemDateTime::resizeEvent(QResizeEvent *)
{

}

void ItemDateTime::timerEvent(QTimerEvent *)
{
    QDateTime date= QDateTime::currentDateTime();


    m_lb0->setText(date.toString("yyyy/MM/dd"));

    m_lb1->setText(date.toString("ap hh:mm:ss"));

}
