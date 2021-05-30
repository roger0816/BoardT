#include "ObjData.h"

ObjData::ObjData(QObject *parent) : QObject(parent)
{
    m_rect = QRect(10,10,300,180);
}

void ObjData::readData(QString sPath)
{
    m_sObjPath = sPath;


    m_sName = m_sObjPath.split("/").last();

    if(m_sObjPath.length()>1)
    {
        m_sLayerName = m_sObjPath.split("/").at(m_sObjPath.split("/").length()-2);
    }



    QSettings conf(m_sObjPath+"/conf.ini",QSettings::IniFormat);

    QString sType = m_dDefine.key(conf.value("Base/type").toInt());


    if(sType.trimmed() == "")
        return ;


    int x = conf.value("Base/x").toInt();

    int y = conf.value("Base/y").toInt();

    int w = conf.value("Base/w").toInt();

    int h = conf.value("Base/h").toInt();


    m_rect.setX(x);

    m_rect.setY(y);

    m_rect.setWidth(w);

    m_rect.setHeight(h);

    m_sType = sType;



    m_dataCmd.sCmd = conf.value("Action/cmd","").toString();

    m_dataCmd.sValue1 = conf.value("Action/value1","").toString();

    m_dataCmd.sValue2 = conf.value("Action/value2","").toString();




    if(sType == E_PIC)
    {

        m_dataPic.iSec = conf.value("Pic/changeTimer",10).toInt();

        m_dataPic.listPicName =conf.value("Pic/list","").toStringList();


        QStringList listCantFind;

        for(int i=0;i<m_dataPic.listPicName.length();i++)
        {
            QString sName = m_dataPic.listPicName.at(i);

            QString sFilePath = m_sObjPath+"/"+sName;

            if(QFileInfo(sFilePath).exists())
            {
                QPixmap p(sFilePath);

                m_dataPic.listPic.append(p);
            }
            else
            {
                listCantFind.append(sName);
            }
        }


        foreach(QString sNoFind,listCantFind)
        {
            m_dataPic.listPicName.removeOne(sNoFind);
        }


    }
    else if(sType == E_VIDEO)
    {
       // m_dataVideo.listName =conf.value("Video/list","").toStringList();

        //QStringList

        m_dataVideo.listName.clear();

        QStringList list = conf.value("Video/list","").toStringList();

        foreach(QString st, list)
        {
            QString s = QApplication::applicationDirPath()+st;

            m_dataVideo.listName.append(s.replace("//","/"));
        }

    }

    else //if(sType == E_TEXT || sType == E_BUTTON || sType == E_MARQUEE || sType == E_QRCODE)
    {


        QString sTitle= sType;

//        if(QFileInfo(m_sObjPath+"/bg.png").exists())
//        {
//            m_dataText.m_sImagePath = m_sObjPath+"/bg.png";
//        }

        m_data.clear();

        conf.beginGroup("Items");
        QStringList keys = conf.childKeys();
        foreach (QString key, keys)
        {
            m_data[key] = conf.value(key);
        }
        conf.endGroup();




        qDebug()<<"AAAAAA : "<<m_data;
    }



}



