#include "cCmd.h"

cCmd::cCmd(QObject *parent) : QObject(parent)
{

}

void cCmd::callCmd(QString sCmd, QString sValue)
{
    int iKey = m_listCmd.indexOf(sCmd.toLower().trimmed());

    qDebug()<<"CMD : "<<sCmd<<" ,value : "<<sValue;

    if(iKey<0 )
    {
        return ;
    }



    switch (iKey)
    {
    case _CHANGE:
    {
        QSettings conf(QCoreApplication::applicationDirPath()+"/data/model0/model0.BDM",QSettings::IniFormat);
        qDebug()<<"do change layer:"<<sValue;
        conf.setValue("Target",sValue.split("/").last());

        conf.setValue("DateTime",QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

        conf.sync();

        break;
    }

    case _TEST:
    {


        QDir().mkdir("C:/work/test");
        break;
    }


    default:

        break;
    }





}
