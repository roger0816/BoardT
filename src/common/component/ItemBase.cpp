#include "ItemBase.h"

ItemBase::ItemBase(QWidget *parent) : QWidget(parent)
{

}

void ItemBase::setPath(QString sPath)
{
    m_sPath= sPath;
    qDebug()<<"BB3";
    init();

    qDebug()<<"BB4";
}

void ItemBase::mousePressEvent(QMouseEvent *)
{
    Global::Instance().setTouch();
}

void ItemBase::timerEvent(QTimerEvent *)
{
    if(Global::Instance().m_iTouchLockTimer>0)
        return;
}

QVariant ItemBase::config(QString sKey)
{
        QSettings conf(m_sPath+"/conf.ini",   QSettings::IniFormat);

        return conf.value(sKey);
}


