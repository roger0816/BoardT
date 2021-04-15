#include "Global.h"


void TouchWidget::mousePressEvent(QMouseEvent *)
{
    emit clicked();
}


Global *Global::m_pInstance = nullptr;

Global::Global()
{

   m_timer.connect(&m_timer,&QTimer::timeout,[=]
   {
        if(m_iTouchLockTimer>0)
            m_iTouchLockTimer-=1000;
   });

   m_timer.start(1000);

   connect(&m_nfc,&FuncNfc::hoverUid,this,&Global::testNfc);

    m_nfc.start();

}

void Global::destory()
{
    qDebug()<<"destory global";

    m_nfc.m_bStop = true;

    m_nfc.wait(1000);

    m_nfc.exit();
}

Global &Global::Instance()
{
    if(m_pInstance==nullptr)
        m_pInstance = new Global();

    return *m_pInstance;
}

void Global::setAllStop(bool bStop)
{
    m_bAllStop = bStop;

    emit callPlay(!m_bAllStop);
}

void Global::setTouch()
{
    m_iTouchLockTimer = m_iResumeSec;
}

void Global::testNfc(QString sUid)
{
    qDebug()<<"test Nfc : "<<sUid;
}

bool Global::isTouchLock()
{
    bool b = true;

    if(m_iTouchLockTimer<=0)
    {
        m_dialogPop->hide();

        b = false;
    }

    return b;
}

QByteArray Global::readFile(QString sFile)
{
    QByteArray byte ;

    QFile file(sFile);

    if(file.open(QIODevice::ReadOnly))
    {
        byte = file.readAll();

        file.close();

    }

    return byte;
}

QString Global::decodeColor(QString sSt)
{
    if(sSt.mid(0,1)=="#")
        sSt.remove(0,1);

    QString sRe ="rgba(%1,%2,%3,%4)";

    if(sSt.length()<6)
        sRe = sRe.arg(0).arg(0).arg(0).arg(0);

    QStringList listTmp = sSt.split(",");

    if(listTmp.length()>=3)
    {
        sRe = sRe.arg(listTmp.at(0).toUInt()).arg(listTmp.at(1).toUInt()).arg(listTmp.at(2).toUInt()).arg(listTmp.at(3).toUInt());
    }
    else
    {
        if(sSt.length()==6)
        {
            sRe="#"+sSt;
        }
        else if(sSt.length()>=8)
        {
            bool b;
            sRe = sRe.arg(sSt.mid(0,2).toUInt(&b,16)).arg(sSt.mid(2,2).toUInt(&b,16)).arg(sSt.mid(4,2).toUInt(&b,16)).arg(sSt.mid(6,2).toUInt(&b,16));

        }
        else
        {
            sRe="rgba(0,0,0,0)";
        }

    }



    return sRe;
}

