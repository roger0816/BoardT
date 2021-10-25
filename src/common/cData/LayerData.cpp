#include "LayerData.h"




LayerData::LayerData(QObject *parent):QObject(parent)
{

}

void LayerData::setPath(QString sPath)
{

    qDeleteAll(m_listData);

    m_listData.clear();

    m_sLayerPath = sPath;

    m_sName = sPath.split("/").last();

    m_sBgPath = sPath+"/bg.png";


    QSettings conf(sPath+"/"+sPath.split("/").last()+".BDT",QSettings::IniFormat);

    m_dataLayer.timeScheduleFrom = QTime::fromString( conf.value("TimeSchedule/from","").toString(),"hhmmss");


    m_dataLayer.timeScheduleTo =  QTime::fromString( conf.value("TimeSchedule/to","").toString(),"hhmmss");

    m_dataLayer.dayOfWeek = conf.value("TimeSchedule/dayOfWeek").toInt();

    m_dataLayer.bStopPreVideo = conf.value("TimeSchedule/stopPreVideo").toBool();

    m_dataLayer.listObjSort = conf.value("ObjSort").toList();

    QFileInfoList listDir = QDir(sPath).entryInfoList(QDir::AllDirs);


    for(int i=0;i<listDir.length();i++)
    {
        QFileInfo dir = listDir.at(i);

        if(dir.fileName()!="." && dir.fileName()!="..")
        {
            QString sObjPath = dir.filePath();


            ObjData *obj = new ObjData(this);

            obj->m_dDefine = m_dDefine;

            obj->readData(sObjPath);

            if(m_dataLayer.listObjSort.indexOf(obj->m_sName)<0)
                m_dataLayer.listObjSort.append(obj->m_sName);


            m_listData.append(obj);


        }

    }

    raise("");

}

void LayerData::raise(QString sObjName)
{
    if(sObjName!="")
    {
        int iIdx = m_dataLayer.listObjSort.indexOf(sObjName);

        if(iIdx<0)
            return ;

        m_dataLayer.listObjSort.move(iIdx,m_dataLayer.listObjSort.length()-1);
    }

    QVariantList lisTmp = m_dataLayer.listObjSort;

    for(int i=0;i<lisTmp.length();i++)
    {
        QString sName = lisTmp.at(i).toString();

        for(int j=0;j<m_listData.length();j++)
        {
            if(sName  ==  m_listData.at(j)->m_sName)
            {
                m_listData.move(j,m_listData.length()-1);
            }
        }

    }
}


