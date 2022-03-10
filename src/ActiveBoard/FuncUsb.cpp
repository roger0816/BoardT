#include "FuncUsb.h"

FuncUsb::FuncUsb(QObject *parent) : QObject(parent)
{
    connect(&m_timer,&QTimer::timeout,this,&FuncUsb::timerout);

    m_timer.start(1000);

    connect(this,&FuncUsb::usbChange,this,&FuncUsb::test);

}

bool FuncUsb::checkUsb(QString sUuid)
{
#ifdef Q_OS_WINDOWS
    return true;
#endif

    bool bRe =false;

    bRe = m_dData.keys().indexOf(sUuid)>=0;

    return bRe;
}

bool FuncUsb::isDevelop(QString sUuid)
{
#ifdef Q_OS_WINDOWS
    return true;
#endif


    bool bRe=false;


    if(sUuid=="")
    {
    if(m_dData.keys().indexOf("98A9-5243")>=0 ||
            m_dData.keys().indexOf("BC5CDF045CDEB87A")>=0 ||
            m_dData.keys().indexOf("5282-9D5B")>=0 ||
            m_dData.keys().indexOf("E6F6-A580")>=0 ||
            m_dData.keys().indexOf("B4D4-2F94")>=0 ||
            m_dData.keys().indexOf("7662D9E862D9ACDD")>=0)
        bRe = true;
     }
    else
    {
        bRe =(sUuid=="98A9-5243" || sUuid=="BC5CDF045CDEB87A" ||sUuid =="7662D9E862D9ACDD"||sUuid =="5282-9D5B"||sUuid =="E6F6-A580"||sUuid =="B4D4-2F94");
    }
    return bRe;
}

bool FuncUsb::differentDevUsb(QString sUuid)
{

    return sUuid!="98A9-5243" && sUuid!="7662D9E862D9ACDD"
            && sUuid!="BC5CDF045CDEB87A"&& sUuid!="5282-9D5B"&& sUuid!="E6F6-A580"&& sUuid!="B4D4-2F94";
}

bool FuncUsb::isReg()
{
    bool b = false;

#ifdef Q_OS_WINDOWS
    return true;
#endif

   // QSettings setting("/usr/share/atb");

    QSettings setting("/home/pi/atb",QSettings::IniFormat);


    if(setting.allKeys().count()>0)
    {
        qDebug()<<"key : "<<setting.allKeys();

        b = true;
    }

    return b;
    //    QString m = setting.value("m","").toString();

    //    QString
}

void FuncUsb::writeReg(QString sUuid)
{
  //  QSettings setting("/usr/share/atb");

     QSettings setting("/home/pi/atb",QSettings::IniFormat);


    setting.setValue("m",sUuid);

    setting.sync();

}

void FuncUsb::removeReg()
{
   // QSettings setting("/usr/share/atb");

    QSettings setting("/home/pi/atb",QSettings::IniFormat);

    setting.clear();

    setting.sync();
}

bool FuncUsb::isLogin(QString sTarget)
{
#ifdef Q_OS_WINDOWS
    return true;
#endif

    bool bRe = false;
   // QSettings setting("/usr/share/atb");

    QSettings setting("/home/pi/atb",QSettings::IniFormat);

    QString sMkey = setting.value("m","AAAAAA").toString();

    if(sTarget=="")
        bRe = m_dData.keys().indexOf(sMkey)>=0;
    else
        bRe =(sMkey==sTarget);



    return bRe;
}

void FuncUsb::timerout()
{
    QProcess p;

#ifndef AA //Q_OS_WINDOWS
    p.start("ls -l /dev/disk/by-uuid/");

    p.waitForFinished();


    QStringList listData = QString(p.readAll()).split("\n");

    QMap<QString,QString> dData;


    foreach(QString st,listData)
    {

        QStringList listTmp = st.split("->");

        QStringList tmpUUid = listTmp.first().split(" ");

        while(tmpUUid.length()>0 &&tmpUUid.last()=="")
            tmpUUid.pop_back();


        QString sUuid="";

        if(tmpUUid.length()>0)
            sUuid = tmpUUid.last().trimmed();

        QString sUsbPath="";

        if(listTmp.length()>0)
            sUsbPath = listTmp.last().trimmed();

        if(sUsbPath.split("/").last().length()>2 && sUsbPath.split("/").last().left(2)=="sd")
            dData.insert(sUuid,"/media/pi/"+sUuid);

    }


#else
    p.start("CMD.EXE /C WMIC.EXE csproduct list full");
#endif


    // qDebug()<<dData.keys();


    if(!m_bFirstTime)
    {
        QSet<QString> addtraction = dData.keys().toSet().subtract(m_dData.keys().toSet());

        QSet<QString> subtraction = m_dData.keys().toSet().subtract(dData.keys().toSet());

        foreach(QString st,addtraction.values())
        {
            emit usbChange(st,"/media/pi/"+st,true);

            m_sLastUsbPath = "/media/pi/"+st;
        }

        foreach(QString st,subtraction.values())
        {
            emit usbChange(st,"/media/pi/"+st,false);
        }
    }

    m_dData = dData;

    m_bFirstTime = false;

}

void FuncUsb::test(QString sUuid, QString sPath, bool bPlunIn)
{
    // qDebug()<<"usb change : "<<bPlunIn<<" , "<<sUuid;
}
