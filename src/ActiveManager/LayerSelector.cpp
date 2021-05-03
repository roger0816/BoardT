#include "LayerSelector.h"

LayerSelector::LayerSelector(QWidget *parent) : QWidget(parent)
{
    m_lay =new QHBoxLayout;




}

void LayerSelector::setData(QMap<QString , QPixmap> dData, QString sPath)
{

    qDebug()<<"selector count : "<<dData.count();

    m_sPath = sPath;

    QSettings conf(sPath+"/conf.ini",QSettings::IniFormat);

    if(dData.keys().length()>0)
    {
       conf.setValue("Target",dData.keys().first());

    }


    while(m_lay->count()>0)
    {
        m_lay->removeItem(m_lay->itemAt(0));

    }


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

//    while(m_listLb.length()<dData.count())
//    {

//        QLabel *lb = new QLabel(this);

//        lb->setAlignment(Qt::AlignHCenter);
//        QFont f;

//        f.setPixelSize(20);

//        lb->setFont(f);


//        m_listLb.append(lb);
//    }

    QStringList listKey = dData.keys();

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

            m_listRadioBtn[i]->show();

        }
        else
        {
            m_listBtn[i]->hide();

            m_listRadioBtn[i]->hide();
        }


    }

    setUiRect();

//        setLayout(m_lay);

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
    int iPicH = height()-24;

    int iPicW = iPicH*1080/1920;

    qDebug()<<"H : "<<iPicH<<" , W :"<<iPicW;

    int iMargin = 10;

    int iCount = 0;

    for(int i=0;i<m_listBtn.length();i++)
    {
        if(m_listBtn[i]->isVisible())
        {
            m_listBtn[i]->setGeometry((iMargin+iPicW)*iCount,0,iPicW,iPicH);



            m_listBtn[i]->setIconSize(m_listBtn[i]->size()*0.9);

            m_listRadioBtn[i]->setGeometry(m_listBtn[i]->x(),iPicH,iPicW,24);

            iCount++;
        }


    }

    setMinimumWidth((iPicW+iMargin)*iCount+10);
}

void LayerSelector::slotClicked()
{
    QPushButton *btn = dynamic_cast<QPushButton*>(sender());

    int iIdx = m_listBtn.indexOf(btn);

    if(iIdx<0 || iIdx >= m_listBtn.length())
    {
        return ;
    }


    for(int i=0;i<m_listBtn.length();i++)
    {

        m_listBtn[i]->setChecked(iIdx==i);
    }

    emit sendSelectLayer(m_listRadioBtn.at(iIdx)->text());

}

void LayerSelector::slotClickedRadio()
{
    QRadioButton * target = dynamic_cast<QRadioButton*>(sender());

  //  int iIdx = m_listRadioBtn.indexOf(target);

    QSettings conf(m_sPath+"/conf.ini",QSettings::IniFormat);


    conf.setValue("Target",target->text());

    conf.sync();


}
