#include "ObjData.h"

ObjData::ObjData(QObject *parent) : QObject(parent)
{

}

void ObjData::setPath(QString sPath)
{
    m_sObjPath = sPath;

    m_sName = m_sObjPath.split("/").last();

    qDebug()<<"obj : name : "<<m_sName<<" , path : "<<m_sObjPath;

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

    if(sType == E_TEXT)
    {


        if(QFileInfo(m_sObjPath+"/bg.png").exists())
        {
            m_dataText.m_sImagePath = m_sObjPath+"/bg.png";
        }

        m_dataText.bIsCent = conf.value("Title/alignCenter").toBool();

        m_dataText.iPixSize = conf.value("Title/txtSize").toInt();

        bool bOk;

        int iBgR = conf.value("Title/bgColor").toString().mid(0,2).toInt(&bOk,16);

        int iBgG = conf.value("Title/bgColor").toString().mid(2,2).toInt(&bOk,16);

        int iBgB = conf.value("Title/bgColor").toString().mid(4,2).toInt(&bOk,16);

        int iBgA = conf.value("Title/bgColor").toString().mid(6,2).toInt(&bOk,16);

        m_dataText.bgColor = QColor(iBgR,iBgG,iBgB,iBgA);

        int iTxR = conf.value("Title/txtColor").toString().mid(0,2).toInt(&bOk,16);

        int iTxG = conf.value("Title/txtColor").toString().mid(2,2).toInt(&bOk,16);

        int iTxB = conf.value("Title/txtColor").toString().mid(4,2).toInt(&bOk,16);

        int iTxA = conf.value("Title/txtColor").toString().mid(6,2).toInt(&bOk,16);


        m_dataText.textColor = QColor(iTxR,iTxG,iTxB,iTxA);

        QFileInfoList listTxt = QDir(m_sObjPath).entryInfoList(QStringList()<<"*.txt");

        qDebug()<<listTxt.first().filePath();

        QString sTxt="";

        QFile file(listTxt.first().filePath());

        if(file.open(QIODevice::ReadOnly))
        {
            sTxt = file.readAll();

            file.close();

        }

        m_dataText.sText = sTxt;


    }





}

