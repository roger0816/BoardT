#include "ScheduleManager.h"

ScheduleManager::ScheduleManager(QObject *parent) : QObject(parent)
{


}



void ScheduleManager::readConfig()
{
    QSettings conf(QApplication::applicationDirPath()+"/../bin/data/model0/model0.BDM",QSettings::IniFormat);

    bool bUpdate = false;

    int iType = conf.value("Schedule/Type","0").toInt();

    if(iType!=m_iType)
        bUpdate = true;

    m_iType = iType;

    QStringList listSleep = conf.value("Schedule/Sleep").toString().split("_");

    if(m_listSleep.join("__") !=listSleep.join("__"))
    {
        bUpdate = true;
    }

    m_listSleep = listSleep;


    QStringList listMulti = conf.value("Schedule/Muti").toStringList();

    if(m_listMulti.join("__") !=listMulti.join("__"))
    {
        bUpdate = true;
    }

    m_listMulti = listMulti;

    int iToday = QDateTime::currentDateTime().date().dayOfWeek();

    QStringList  listOne = conf.value("Schedule/W"+QString::number(iToday)).toString().split("_");



    if(m_listOne.join("__") !=listOne.join("__"))
    {
        bUpdate = true;
    }

    m_listOne = listOne;





    if(bUpdate)
    {
        m_iMultiIdx=-1;

        m_iMultiDelay = 0;


    }

}

bool ScheduleManager::multiSchedule(QString &sLayerName)
{
    sLayerName="";

    qDebug()<<"multi schedule";

    if(m_listMulti.length()<0)
        return false;


    if(m_iMultiDelay>0)
    {
        m_iMultiDelay-=m_iDefineSubMsec;
        return false;

    }
    else
    {
        m_iMultiIdx++;

        if(m_iMultiIdx>=m_listMulti.length())
            m_iMultiIdx=0;


        QStringList listTmp =  m_listMulti.at(m_iMultiIdx).split("_");

        while(listTmp.length()<3)
            listTmp.append("");

        QTime t(QTime::fromString(listTmp.at(1),"hh:mm:ss"));

        m_iMultiDelay = t.hour()*60*60*1000 + t.minute()*60*1000 + t.second()*1000;

        sLayerName = listTmp.at(0);

        return true;

    }

}

bool ScheduleManager::oneSchedule(QString &sLayerName)
{

    sLayerName="";

    QStringList list = m_listOne;

    while(list.length()<4)
        list.append("");

    if(list.at(0).toInt()==1)
    {
        QTime s(QTime::fromString(list.at(1),"hh:mm:ss"));

        QTime t(QTime::fromString(list.at(2),"hh:mm:ss"));

        QTime current(QTime::currentTime());

        if(current >= s && current<t)
        {
            sLayerName = list.at(3);

        }

    }

    return true;
}

bool ScheduleManager::checkSleep()
{
    bool bSleep = false;


    QStringList list = m_listSleep;

    while(list.length()<3)
        list.append("");

    if(list.at(0).toInt()==1)
    {
        QTime s(QTime::fromString(list.at(1),"hh:mm:ss"));

        QTime t(QTime::fromString(list.at(2),"hh:mm:ss"));

        QTime current(QTime::currentTime());

        if(current >= s && current<t)
        {

            bSleep = true;
        }

    }

    return bSleep;


    return bSleep;
}


void ScheduleManager::check(int iMsec)
{

    m_iDefineSubMsec = iMsec;

    qDebug()<<"schedule ";
    readConfig();

    QString sCurrent = CCTRL.layerName();

    bool bIsSleep = checkSleep();

    if(bIsSleep)
    {

        m_bSleep = true;
        if(sCurrent!="")
            CCTRL.changeLayer("");

        return;
    }
    else
    {
        if(m_bSleep)
        {
            m_bSleep = false;

           CCTRL.changeLayer(CCTRL.preLayerName());

           return;
        }

    }



    if(m_iType<=0)
        return;




    QString sTarget ="";

    bool bUpdate = false;

    if(m_iType==1)
    {
        bUpdate =multiSchedule(sTarget);
    }

    else if(m_iType==2)
    {
        bUpdate =oneSchedule(sTarget);
    }



    if(sCurrent!= sTarget &&bUpdate)
        CCTRL.changeLayer(sTarget);

}
