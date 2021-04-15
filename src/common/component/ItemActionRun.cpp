#include "ItemActionRun.h"

ItemActionRun::ItemActionRun(QWidget *parent) : ItemPic(parent)
{

}

bool ItemActionRun::init()
{
    bool b = false;

    QString sPath = m_sPath;

    QFileInfoList list = QDir(sPath).entryInfoList(QStringList()<<"*.png"<<"*.PNG");

    m_listPic.clear();

    for(int i=0;i<list.length();i++)
    {
        m_listPic.append(list.at(i).filePath());

        QString sUrlFile = sPath+"/"+list.at(i).baseName()+".txt";

        QFile file(sUrlFile);

        QString sUrl="";

        if(file.open(QIODevice::ReadOnly))
        {
            sUrl.append(file.readAll().trimmed());

            file.close();
        }

        m_listUrl.append(sUrl);


        b = true;

    }

    if(m_listPic.length()>0)
        setPic(m_listPic.first());


    QSettings conf(sPath+"/conf.ini",QSettings::IniFormat);

    m_iChangeSec = conf.value("Base/changeTimer").toInt()*1000;

    m_popRect.setSize(QSize(conf.value("Pop/w").toInt(),conf.value("Pop/h").toInt()));

    m_popRect.setX(conf.value("Pop/x").toInt());

    m_popRect.setY(conf.value("Pop/y").toInt());

    startTimer(qBound(1000,m_iChangeSec,60*60*60*1000));

    return b;
}

void ItemActionRun::mousePressEvent(QMouseEvent *e)
{
    ItemBase::mousePressEvent(e);

    Global::Instance().m_dialogPop->setActionRun(m_listPic,m_listUrl,m_popRect);


}

void ItemActionRun::timerEvent(QTimerEvent *)
{


    if(Global::Instance().isTouchLock())
        return;

    if(m_listPic.length()<1 || Global::Instance().allStop())
        return ;

    //always 0
    m_iIdx=0;
    QString sFile = m_listPic[0];

    setPic(sFile);
}
