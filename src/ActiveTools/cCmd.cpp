#include "cCmd.h"

cCmd::cCmd(QObject *parent) : QObject(parent)
{

}

void cCmd::callCmd(QString sCmd, QString sValue)
{

    qDebug()<<"CMD : "<<sCmd<<" ,value : "<<sValue;






    if(sCmd ==CMD_Page || sCmd ==CMD_PageNoStop )
    {
        QSettings conf(QCoreApplication::applicationDirPath()+"/data/model0/model0.BDM",QSettings::IniFormat);
        qDebug()<<"do change layer:"<<sValue;
        conf.setValue("Target",sValue.split("/").last());

        conf.setValue("DateTime",QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

        conf.setValue("VideoStatus","0");

        if(sCmd ==CMD_PageNoStop)
        {
            conf.setValue("VideoStatus","1");

        }

        conf.sync();

    }









}
