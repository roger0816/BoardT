#include "ObjData.h"

ObjData::ObjData(QObject *parent) : QObject(parent)
{
    m_rect = QRect(10,10,300,180);
}

void ObjData::setPath(QString sPath)
{
    m_sObjPath = sPath;


    m_sName = m_sObjPath.split("/").last();

    if(m_sObjPath.length()>1)
    {
        m_sLayerName = m_sObjPath.split("/").at(m_sObjPath.split("/").length()-2);
    }


    qDebug()<<"obj : name : "<<m_sName<<" , path : "<<m_sObjPath;

    QSettings conf(m_sObjPath+"/conf.ini",QSettings::IniFormat);

    QString sType = m_dDefine.key(conf.value("Base/type").toInt());

    qDebug()<<"BB0:"<<m_dDefine;


    if(sType.trimmed() == "")
        return ;


    int x = conf.value("Base/x").toInt();

    int y = conf.value("Base/y").toInt();

    int w = conf.value("Base/w").toInt();

    int h = conf.value("Base/h").toInt();

    qDebug()<<"x : "<<x<<" , y :"<<y<<" , w:"<<w<<" , h:"<<h;

    m_rect.setX(x);

    m_rect.setY(y);

    m_rect.setWidth(w);

    m_rect.setHeight(h);

    m_sType = sType;

    if(sType == E_TEXT || sType == E_BUTTON || sType == E_MARQUEE || sType == E_QRCODE)
    {

        QString sTitle= sType;


        if(QFileInfo(m_sObjPath+"/bg.png").exists())
        {
            m_dataText.m_sImagePath = m_sObjPath+"/bg.png";
        }

        m_dataText.bIsCent = conf.value(sTitle+"/alignCenter",1).toBool();

        m_dataText.iPixSize = conf.value(sTitle+"/txtSize","30").toInt();

        QString sFontSt = conf.value(sTitle+"/font","Arial,24,-1,5,50,0,0,0,0,0,Regular").toString();

        if(sFontSt!="" && sFontSt.split(",").length()>5)
            m_dataText.font.fromString(sFontSt);

        bool bOk;

        int iBgR = conf.value(sTitle+"/bgColor","ff").toString().mid(0,2).toInt(&bOk,16);

        int iBgG = conf.value(sTitle+"/bgColor","ff").toString().mid(2,2).toInt(&bOk,16);

        int iBgB = conf.value(sTitle+"/bgColor","ff").toString().mid(4,2).toInt(&bOk,16);

        int iBgA = conf.value(sTitle+"/bgColor","ff").toString().mid(6,2).toInt(&bOk,16);

        m_dataText.bgColor = QColor(iBgR,iBgG,iBgB,iBgA);

        int iTxR = conf.value(sTitle+"/txtColor","00").toString().mid(0,2).toInt(&bOk,16);

        int iTxG = conf.value(sTitle+"/txtColor","00").toString().mid(2,2).toInt(&bOk,16);

        int iTxB = conf.value(sTitle+"/txtColor","00").toString().mid(4,2).toInt(&bOk,16);

        int iTxA = conf.value(sTitle+"/txtColor","ff").toString().mid(6,2).toInt(&bOk,16);


        m_dataText.textColor = QColor(iTxR,iTxG,iTxB,iTxA);


        m_dataText.sText = conf.value(sTitle+"/text").toString();

        if(sType == E_MARQUEE)
        {
            m_dataMar.listText =conf.value(sTitle+"/list","").toStringList();

            m_dataMar.iSpeed = conf.value(sTitle+"/speed").toInt();



        }

    }

    else if(sType == E_PIC)
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
            QString s = "/home/pi/work/bin"+st;

            m_dataVideo.listName.append(s.replace("//","/"));
        }

    }



}



