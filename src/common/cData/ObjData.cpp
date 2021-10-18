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
            QString sFilePath = m_dataPic.listPicName.at(i);

            if(!QFileInfo(sFilePath).exists())
                sFilePath = m_sObjPath+"/"+sFilePath.split("/").last();

            if(QFileInfo(sFilePath).exists())
            {
                QPixmap p(sFilePath);

                m_dataPic.listPic.append(p);
            }
            else
            {
                listCantFind.append(m_dataPic.listPicName.at(i));
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


        m_dataVideo.listName.clear();

        QStringList list = conf.value("Video/list","").toStringList();

        foreach(QString sFilePath, list)
        {
            //            qDebug()<<"read: "<<sFilePath ;
            //            if(!QFileInfo(sFilePath).exists())
            sFilePath = m_sObjPath+"/"+sFilePath.split("/").last();
            m_dataVideo.listName.append(sFilePath);
        }

        m_dataVideo.bIsMute =conf.value("Video/mute").toBool();

        m_dataVideo.sRtsp = conf.value("Video/rtsp").toString().trimmed();

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




        qDebug()<<"read itemdata : "<<m_data;
    }



}

void ObjData::writeData()
{

    QDir().mkdir(m_sObjPath);

    QSettings conf(m_sObjPath+"/conf.ini",QSettings::IniFormat);

    if(m_sType.trimmed() == "")
        return ;


    int  x = m_rect.x();

    int y = m_rect.y();

    int w = m_rect.width();

    int h = m_rect.height();

    conf.setValue("Base/type",m_dDefine[m_sType]);

    qDebug()<<"write : "<<m_sObjPath<<"type : "<<m_dDefine[m_sType]<<", "<<m_sType;


    conf.setValue("Base/x",x);

    conf.setValue("Base/y",y);

    conf.setValue("Base/w",w);

    conf.setValue("Base/h",h);

    conf.setValue("Base/changeTimer",5);

    conf.setValue("Action/cmd",m_dataCmd.sCmd);

    conf.setValue("Action/value1",m_dataCmd.sValue1);

    conf.setValue("Action/value2",m_dataCmd.sValue2);

    conf.sync();

    if(m_sWaitRename.trimmed()!="")
    {
        deleteDirectory(m_sWaitRename);

        m_sWaitRename = "";
    }


    if(m_sType == E_PIC)
    {


        QStringList listName = m_dataPic.listPicName;


        conf.setValue("Pic/list",listName);


        conf.setValue("Pic/changeTimer",m_dataPic.iSec);


        for(int i=0;i<listName.length();i++)
        {
            QPixmap *p = & m_dataPic.listPic[i];

            p->save(m_sObjPath+"/"+listName.at(i).split("/").last());
        }

    }

    else if(m_sType == E_VIDEO)
    {



        QStringList listName = m_dataVideo.listName;


        for(int i=0;i<listName.length();i++)
        {
            //            QFile file(listName.at(i));

            //            if(file.open(QIODevice::ReadOnly))
            //            {
            //                file.copy(m_sObjPath+"/"+listName.at(i).split("/").last());

            //                file.close();
            //            }

            QString sTarget =listName.at(i).split("/").last();
            qDebug()<<"file : "<<listName.at(i);
            qDebug()<<"save : "<<sTarget;
            QFile::copy(listName.at(i),sTarget);

            listName[i] = sTarget;

        }

        conf.setValue("Video/mute",m_dataVideo.bIsMute);

        conf.setValue("Video/rtsp",m_dataVideo.sRtsp);

        conf.setValue("Video/list",listName);

    }

    else
    {


        //

        QStringList listKey = m_data.keys();

        conf.beginGroup("Items");


        if(m_data[Label::imagePath].toString()!="")
        {

            QImage image(m_data["originImage"].toString());

            image.save(m_sObjPath+"/bg.png");

            m_data[Label::imagePath] = m_sObjPath.split("bin").last()+"/bg.png";
        }

        for(int i=0;i<listKey.length();i++)
        {

            QString sKey = listKey.at(i);


            QVariant target = m_data[sKey];

            conf.setValue(sKey,target);

        }

        conf.endGroup();

        conf.sync();


        qDebug()<<"write itemdata : "<<m_data;
    }

}

bool ObjData::deleteDirectory(const QString &path)
{
    if (path.isEmpty())
        return false;

    QDir dir(path);
    if(!dir.exists())
        return true;

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList)
    {
        if (fi.isFile())
            fi.dir().remove(fi.fileName());
        else
            deleteDirectory(fi.absoluteFilePath());
    }
    return dir.rmpath(dir.absolutePath());

}



