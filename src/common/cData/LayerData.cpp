#include "LayerData.h"




//---------
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

    qDebug()<<"layer name : "<<m_sName<<" path : "<<m_sLayerPath;

    QFileInfoList listDir = QDir(sPath).entryInfoList(QDir::AllDirs);


    for(int i=0;i<listDir.length();i++)
    {
        QFileInfo dir = listDir.at(i);

        if(dir.fileName()!="." && dir.fileName()!="..")
        {

            ObjData *obj = new ObjData(this);

            obj->m_dDefine = m_dDefine;

            obj->setPath(dir.filePath());

            m_listData.append(obj);



        }

    }




}

