#include "CData.h"

CData *CData::m_pInstance = nullptr;


CData &CData::Instance()
{
    if(m_pInstance==nullptr)
        m_pInstance = new CData();

    return *m_pInstance;
}

void CData::createModel(QString sPath)
{
    m_sPath = sPath;
    qDebug()<<"create model : "<<sPath;
  //  QSettings define(m_sPath+"/define.ini",QSettings::IniFormat);

    QSettings pro(m_sPath+"/"+m_sPath.split("/").last()+".BDM",QSettings::IniFormat);

    QStringList listKey = m_dData.keys();

    pro.setValue("Target","layer0");

    pro.setValue("DateTime",QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

    pro.sync();

    QDir().mkdir(m_sPath+"/layer0");



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

void CData::writeModel()
{


    if(!QDir(m_sPath).exists())
    {
        QDir().mkdir(m_sPath);
    }

    QSettings defin(m_sPath+"/define.ini",QSettings::IniFormat);

    QStringList listDfKey = m_dDefine.keys();

    for(int j=0;j<listDfKey.length();j++)
    {
        QString sKey = listDfKey.at(j);

        defin.setValue(sKey,m_dDefine[sKey]);
    }

    defin.sync();

    QSettings pro(m_sPath+"/"+m_sPath.split("/").last()+".BDM",QSettings::IniFormat);

    QStringList listKey = m_dData.keys();


    pro.sync();


    for(int i=0;i<listKey.length();i++)
    {
        LayerData *layerData = m_dData[listKey.at(i)];

        QString sPath = layerData->m_sLayerPath;

        QSettings conf(sPath+"/"+sPath.split("/").last()+".BDT",QSettings::IniFormat);

        conf.setValue("Base/resumeTimer",15);

        conf.sync();


        if(layerData->m_sBgPath=="")
        {
            if(QFileInfo(sPath+"/bg.png").exists())
            {
                QFile(sPath+"/bg.png").remove();
            }
        }
        else if(layerData->m_sBgPath!="" && layerData->m_sBgPath !=sPath+"/bg.png")
        {
            QImage image(layerData->m_sBgPath);

            image.save(sPath+"/bg.png");

        }



        foreach(ObjData *item ,layerData->m_listData)
        {
            writeObj(item);
        }


    }




}

void CData::checkDefine(QString sPath, QMap<QString, int> defData)
{
    QSettings define(sPath+"/define.ini",QSettings::IniFormat);

    QStringList defKey = define.allKeys();

    QStringList checkKey = defData.keys();



    for(int i=0;i<checkKey.length();i++)
    {
        if(defKey.indexOf(checkKey[i])<0)
        {

            define.setValue(checkKey[i],defData[checkKey[i]]);
        }


    }



    define.sync();

}

void CData::writeObj(ObjData *item)
{

    QString sItemPash = item->m_sObjPath;

    QDir().mkdir(sItemPash);


    QSettings conf(sItemPash+"/conf.ini",   QSettings::IniFormat);


    int  x = item->m_rect.x();

    int y = item->m_rect.y();

    int w = item->m_rect.width();

    int h = item->m_rect.height();

    conf.setValue("Base/x",x);

    conf.setValue("Base/y",y);

    conf.setValue("Base/w",w);

    conf.setValue("Base/h",h);

    conf.setValue("Base/changeTimer",5);

    if(item->m_sType == E_TEXT || item->m_sType == E_BUTTON
            ||item->m_sType == E_MARQUEE || item->m_sType == E_QRCODE )
    {

        QString sTitle = item->m_sType;


        conf.setValue("Base/type",m_dDefine[item->m_sType]);

        if(item->m_dataText.m_sImagePath!="")
        {
            QImage image(item->m_dataText.m_sImagePath);

            image.save(sItemPash+"/bg.png");


            item->m_dataText.m_sImagePath = sItemPash+"/bg.png";
        }
        conf.setValue(sTitle+"/bgPath",item->m_dataText.m_sImagePath);

        conf.setValue(sTitle+"/font",item->m_dataText.font.toString());

        conf.setValue(sTitle+"/text",item->m_dataText.sText);

        int iTemp = item->m_dataText.bIsCent;

        conf.setValue(sTitle+"/alignCenter",iTemp);



        QString sRgba("%1%2%3%4");


        QString sTxtColor = sRgba.arg(item->m_dataText.textColor.red(),2,16,QLatin1Char( '0' ))
                .arg(item->m_dataText.textColor.green(),2,16,QLatin1Char( '0' ))
                .arg(item->m_dataText.textColor.blue(),2,16,QLatin1Char( '0' ))
                .arg(item->m_dataText.textColor.alpha(),2,16,QLatin1Char( '0' ));

        QString sBgColor = sRgba.arg(item->m_dataText.bgColor.red(),2,16,QLatin1Char( '0' ))
                .arg(item->m_dataText.bgColor.green(),2,16,QLatin1Char( '0' ))
                .arg(item->m_dataText.bgColor.blue(),2,16,QLatin1Char( '0' ))
                .arg(item->m_dataText.bgColor.alpha(),2,16,QLatin1Char( '0' ));

        conf.setValue(sTitle+"/txtColor",sTxtColor);

        conf.setValue(sTitle+"/bgColor",sBgColor);

        if(item->m_sType == E_MARQUEE)
        {
            conf.setValue(sTitle+"/speed",item->m_dataMar.iSpeed);

            conf.setValue(sTitle+"/list",item->m_dataMar.listText);
        }


    }

    else if(item->m_sType == E_PIC)
    {

        conf.setValue("Base/type",m_dDefine[E_PIC]);

        QStringList listName = item->m_dataPic.listPicName;


        conf.setValue("Pic/list",listName);


        conf.setValue("Pic/changeTimer",item->m_dataPic.iSec);


        for(int i=0;i<listName.length();i++)
        {
            QPixmap *p = & item->m_dataPic.listPic[i];

            p->save(sItemPash+"/"+listName.at(i));
        }

    }

    else if(item->m_sType == E_VIDEO)
    {

        conf.setValue("Base/type",m_dDefine[E_VIDEO]);

        QStringList listName = item->m_dataVideo.listName;

        QStringList list;

        foreach(QString st ,listName)
        {
            QString s ="/"+ st.split("bin").last();


            list.append(s);
        }

        conf.setValue("Video/list",list);

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
    QString sDef = QApplication::applicationDirPath()+"/data/model0";


    QMap<QString, int > def;

    def.insert("text",1);

    def.insert("pic",2);

    def.insert("button",3);

    def.insert("dateTime",4);

    def.insert("web",5);
    def.insert("function",6);

    def.insert("video",7);
    def.insert("logo",8);

    def.insert("ticket",9);
    def.insert("active",10);
    def.insert("qrcode",11);

    def.insert("onSale",14);
    def.insert("mediaCent",17);

    def.insert("marquee",21);

    checkDefine(sDef,def);
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



