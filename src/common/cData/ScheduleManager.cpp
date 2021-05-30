#include "ScheduleManager.h"

ScheduleManager::ScheduleManager(QObject *parent) : QObject(parent)
{

}

void ScheduleManager::startModel(QString sPath)
{

    m_sPath = sPath;

    QSettings pro(m_sPath+"/"+m_sPath.split("/").last()+".BDM",QSettings::IniFormat);

    m_sCurrentLayer = pro.value("Target","def").toString();

}

bool ScheduleManager::checkTimeSchedule()
{
    QDateTime cuDate =QDateTime::currentDateTime();


    QStringList listKey = CDATA.m_dData.keys();

    QTime fromDate;
    int iFrom;


    QTime toDate;

    int iTo;



    for(int i=0;i<listKey.length();i++)
    {


        QString key = listKey.at(i);

        if(CDATA.m_dData[key] != nullptr)
        {

            fromDate = CDATA.m_dData[key]->m_dataLayer.timeScheduleFrom;

            toDate = CDATA.m_dData[key]->m_dataLayer.timeScheduleTo;

            iFrom = CDATA.m_dData[key]->m_dataLayer.dayOfWeek;

            iTo = iFrom;

            if(fromDate > toDate)
            {
                iTo =iFrom+1;
            }

        }
    }





}
