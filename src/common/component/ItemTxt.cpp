#include "ItemTxt.h"

ItemTxt::ItemTxt(QWidget *parent) : ItemBase(parent)
{

    m_wBg = new QWidget(this);



    m_lb = new QLabel(m_wBg);

    m_ani = new QPropertyAnimation(m_lb,"geometry",this);

    connect(m_ani,&QPropertyAnimation::finished,this,&ItemTxt::aniFinished);

   m_ani->setDuration(10000);


}

bool ItemTxt::init()
{



    QFont f;

    f.setPixelSize(config("Title/txtSize").toInt()*Global::Instance().m_fDiffSize);

    m_lb->setFont(f);

    m_lb->setStyleSheet("color:"+Global::Instance().decodeColor(config("Title/txtColor").toString())+";"+
                        "background-color:rgba(0,0,0,0);");

    m_wBg->setObjectName("ItemTxt_m_wBg");

    if(QFileInfo(m_sPath+"/bg.png").exists())
    {
        m_wBg->setStyleSheet("QWidget#ItemTxt_m_wBg{border-image:url("+m_sPath+"/bg.png);}");

    }
    else
        m_wBg->setStyleSheet("QWidget#ItemTxt_m_wBg{background-color:"+Global::Instance().decodeColor(config("Title/bgColor").toString())+";}");


    m_bMarquee = config("Title/marquee").toBool();

    if(!m_bMarquee)
    {
        if(config("Title/alignCenter").toBool())
            m_lb->setAlignment(Qt::AlignCenter);

    }



    QFileInfoList list = QDir(m_sPath).entryInfoList(QStringList()<<"*.txt");

    m_listTxt.clear();

    foreach(QFileInfo target,list)
    {
        QFile file(target.filePath());

        if(file.open(QIODevice::ReadOnly))
        {

            m_listTxt.append(getFileData(file.readAll()));

        }

        file.close();

    }


    if(m_listTxt.length()>0)
        m_lb->setText(m_listTxt.at(0));


    return true;
}

void ItemTxt::showEvent(QShowEvent *)
{
    m_wBg->setGeometry(0,0,width(),height());


    if(m_bMarquee)
    {
       // QTimer::singleShot(500,this,SLOT(startMarquee));

        startMarquee();

    }

        m_lb->resize(size());
}

QStringList ItemTxt::getFileData(QByteArray dData)
{

    QStringList listRe;

    QString sTmp(dData);


    QStringList listTmp = QString(dData).split("\n");

    foreach(QString st,listTmp)
    {
        st = st.replace("\n","").trimmed();

        st = st.replace("\r","").trimmed();

        if(st.length()>0)
            listRe.append(st);
    }


    return listRe;

}

void ItemTxt::startMarquee()
{

    if(m_listTxt.length()<1)
        return ;


    m_ani->setStartValue(QRect(width(),0,width(),height()));

    m_ani->setEndValue(QRect(-(m_lb->width()-100),0,width(),height()));

    m_ani->start();
}

void ItemTxt::aniFinished()
{

    m_iIdx++;

    if(m_iIdx>=m_listTxt.length())
        m_iIdx=0;

    m_lb->setText(m_listTxt.at(m_iIdx));

    startMarquee();


}
