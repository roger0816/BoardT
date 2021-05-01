#include "CData.h"

CData *CData::m_pInstance = nullptr;


CData &CData::Instance()
{
    if(m_pInstance==nullptr)
        m_pInstance = new CData();

    return *m_pInstance;
}

void CData::readModel(QString sPath)
{
    qDebug()<<"read model : "<<sPath;

    m_sPath = sPath;

    m_sModelName = m_sPath.split("/").last();

    typeMapping();

    qDeleteAll(m_dData);

    m_dData.clear();



    QFileInfoList listDir = QDir(sPath).entryInfoList(QDir::AllDirs);



    for(int i =0; i<listDir.length(); i++)
    {

        QFileInfo dir = listDir.at(i);

        if(dir.fileName()!="." && dir.fileName()!="..")
        {

            LayerData *layer = new LayerData(this);

            layer->m_dDefine = m_dDefine;

            layer->setPath(dir.filePath());


            m_dData.insert(dir.fileName(),layer);
        }


    }



}

void CData::addLayer(QString sPath)
{
    LayerData *layer = new LayerData(this);

    layer->m_dDefine = m_dDefine;

    layer->setPath(sPath);

    m_dData.insert(sPath.split("/").last(),layer);

    qDebug()<<"add layer : "<<sPath<<" , data count : "<<m_dData.count();
}

ObjData *CData::getObj(QString layer, QString objName, bool &bOk)
{
    bOk = false;

    if(m_dData.keys().indexOf(layer)>=0)
    {
        for(int i=0;i<m_dData[layer]->m_listData.length();i++)
        {
            if(m_dData[layer]->m_listData[i]->m_sName == objName)
            {
               bOk = true;

               return m_dData[layer]->m_listData[i];
            }

        }

    }


    return new ObjData;

}




CData::CData(QObject *parent) : QObject(parent)
{

}

void CData::typeMapping()
{
    QSettings defin(m_sPath+"/define.ini",QSettings::IniFormat);

    m_dDefine.clear();

    QStringList listDefineKey= defin.allKeys();

    for(int i=0; i < listDefineKey.length();i++)
    {
        QString sKey = listDefineKey.at(i);

        int iValue = defin.value(sKey).toInt();

        qDebug()<<sKey<<" , "<<iValue;

        m_dDefine.insert(sKey,iValue);
    }
}

