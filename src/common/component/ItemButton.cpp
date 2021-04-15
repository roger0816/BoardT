#include "ItemButton.h"

ItemButton::ItemButton(QWidget *parent) : ItemBase(parent)
{
    m_btn =new QPushButton(this);

   m_btn->setFocusPolicy(Qt::NoFocus);
    m_btn->show();

    connect(m_btn,&QPushButton::clicked,this,&ItemButton::clicked);
}

void ItemButton::showEvent(QShowEvent *)
{
    m_btn->resize(size());
}

bool ItemButton::init()
{
    QFont f;

    f.setPixelSize(config("Title/txtSize").toUInt());

    m_btn->setFont(f);

    m_btn->setStyleSheet("color:"+Global::Instance().decodeColor(config("Title/txtColor").toString())+";"+
                        "background-color:"+Global::Instance().decodeColor(config("Title/bgColor").toString())+";");


    m_btn->setText(config("Base/text").toString());


    QSettings conf(m_sPath+"/conf.ini",   QSettings::IniFormat);

    conf.beginGroup("Gpio");

    QStringList listKey = conf.allKeys();

    for(int i=0;i<listKey.length();i++)
    {
        QString sKey = listKey[i];

        int iValue = conf.value(listKey[i]).toInt();

        m_gpio.insert(sKey.replace("pin","").trimmed(),iValue);

        QString sTmp ="echo "+sKey.replace("pin","").trimmed()+" > /sys/class/gpio/export ";

        system(sTmp.toStdString().c_str());


        QString sTmp2 ="echo out > /sys/class/gpio/gpio"+sKey.replace("pin","").trimmed()
                +"/direction";

        system(sTmp2.toStdString().c_str());

    }


}

void ItemButton::clicked()
{
    QStringList listKey= m_gpio.keys();

    QString sTmp="echo %2 > /sys/class/gpio/gpio%1/value";

    for(int i=0;i<listKey.length();i++)
    {
        QString sKey= listKey.at(i);

        int iValue = m_gpio.value(sKey);

       // qDebug()<<sTmp.arg(sKey).arg(iValue);
        system(sTmp.arg(sKey).arg(m_gpio.value(sKey)).toStdString().c_str());
    }

}
