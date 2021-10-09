#include "LayerSelector.h"

LayerSelector::LayerSelector(QWidget *parent) : QWidget(parent)
{

}

void LayerSelector::setData(QMap<QString , QPixmap> dData, QString sPath)
{

    qDebug()<<"selector count : "<<dData.count();

    m_sPath = sPath;

    // QSettings conf(sPath+"/conf.ini",QSettings::IniFormat);

    QSettings conf(m_sPath+"/"+m_sPath.split("/").last()+".BDM",QSettings::IniFormat);

    QString sTarget = conf.value("Target","").toString();

    if(dData.keys().length() <= 0)
        return;


    if(sTarget=="")
    {

        sTarget = dData.keys().first();

        conf.setValue("Target","def");
    }

    QStringList listKey = dData.keys();

    int iDef = listKey.indexOf("def");

    if(iDef>=0 && iDef < listKey.length())
        listKey.move(iDef,0);

    int iIdxRadio = qBound(0,listKey.indexOf(sTarget),listKey.length()-1);





    while(m_listBtn.length()<dData.count())
    {
        QPushButton *btn = new QPushButton(this);

        btn->setCheckable(true);

        connect(btn,&QPushButton::clicked,this,&LayerSelector::slotClicked);

        m_listBtn.append(btn);
    }


    while(m_listRadioBtn.length()<dData.count())
    {
        QRadioButton *btn = new QRadioButton(this);

        //  lb->setAlignment(Qt::AlignHCenter);

        connect(btn,&QRadioButton::clicked,this,&LayerSelector::slotClickedRadio);

        QFont f;

        f.setPixelSize(20);

        btn->setFont(f);


        m_listRadioBtn.append(btn);
    }




    for(int i=0;i<m_listBtn.length();i++)
    {
        // m_listBtn[i]->setStyleSheet("border-image:url("+list.)
        if(i<listKey.length())
        {

            m_listBtn[i]->setIcon(QIcon(dData[listKey.at(i)]));

            m_listBtn[i]->show();

            //            m_lay->addWidget(m_listBtn[i]);

            //     m_listLb[i]->setText(listKey.at(i));

            m_listRadioBtn[i]->setText(listKey.at(i));


            m_listRadioBtn[i]->setChecked(i==iIdxRadio);

            m_listRadioBtn[i]->show();



        }
        else
        {
            m_listBtn[i]->hide();

            m_listRadioBtn[i]->hide();


        }


    }

//    m_sCurrentPath = m_sPath+"/"+m_listRadioBtn[qBound(0,iIdxRadio,m_listRadioBtn.length()-1)]->text();

    emit m_listRadioBtn[iIdxRadio]->clicked();

    setUiRect();

    //        setLayout(m_lay);

}

void LayerSelector::toDef()
{
    if(m_listBtn.length()>0)
    {
        emit m_listBtn.first()->click();


        emit m_listRadioBtn.first()->click();

    }
}

void LayerSelector::resizeEvent(QResizeEvent *)
{
    setUiRect();
}

void LayerSelector::showEvent(QShowEvent *)
{
    setUiRect();
}

void LayerSelector::setUiRect()
{
    int iPicH = 180;

    int iPicW = iPicH*1080/1920;

    qDebug()<<"H : "<<iPicH<<" , W :"<<iPicW;

    int iMargin = 30;

    int iCount = 0;

    for(int i=0;i<m_listBtn.length();i++)
    {
        if(m_listBtn[i]->isVisible())
        {

            m_listBtn[i]->setGeometry(40,(iMargin+iPicH)*iCount,iPicW,iPicH);

            m_listBtn[i]->setIconSize(m_listBtn[i]->size()*0.9);

            m_listRadioBtn[i]->setGeometry(10,m_listBtn[i]->y(),iPicW,26);

            iCount++;
        }


    }


    setMinimumHeight((iPicH+iMargin)*iCount+10);
    // setMinimumWidth((iPicW+iMargin)*iCount+10);
}

void LayerSelector::setIdx(int iIdx)
{
    if(iIdx<0 || iIdx >= m_listBtn.length())
    {
        return ;
    }


    for(int i=0;i<m_listBtn.length();i++)
    {

        m_listBtn[i]->setChecked(iIdx==i);
    }

    for(int i=0;i<m_listRadioBtn.length();i++)
    {
        m_listRadioBtn[i]->setChecked(i==iIdx);
    }

    emit sendSelectLayer(m_listRadioBtn.at(iIdx)->text());

    m_sCurrentPath = m_sPath+"/"+m_listRadioBtn.at(iIdx)->text();

    m_sSetTargetPath = m_sCurrentPath;



}



void LayerSelector::slotClicked()
{
    QPushButton *btn = dynamic_cast<QPushButton*>(sender());

    setIdx(m_listBtn.indexOf(btn));

}

void LayerSelector::slotClickedRadio()
{
    QRadioButton * target = dynamic_cast<QRadioButton*>(sender());


    setIdx(m_listRadioBtn.indexOf(target));

//    QSettings conf(m_sPath+"/"+m_sPath.split("/").last()+".BDM",QSettings::IniFormat);


//    QString sPre = conf.value("Target","").toString();

//    if(sPre != target->text())
//    {
//        conf.setValue("Target",target->text());

//        conf.setValue("DateTime",QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

//        conf.sync();



//    }

}

