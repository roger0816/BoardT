#include "ItemTicket.h"
#include "ui_ItemTicket.h"

ItemTicket::ItemTicket(QWidget *parent) :
    ItemBase(parent),
    ui(new Ui::ItemTicket)
{
    ui->setupUi(this);

    m_listSelectBtn<<ui->btn1<<ui->btn2<<ui->btn3<<ui->btn4
                  <<ui->btn5<<ui->btn6<<ui->btn7;

    foreach(QPushButton *btn,m_listSelectBtn)
    {
        connect(btn,&QPushButton::clicked,this,&ItemTicket::clickSelect);
    }
}

ItemTicket::~ItemTicket()
{
    delete ui;
}

bool ItemTicket::init()
{
    bool b= false;

    QString sIcon = m_sPath+"/icon.png";

    QString sStyle = "border-image:url(\""+sIcon+"\");";

    ui->lb->setStyleSheet(sStyle);

    QStringList listTempInfo = QString(Global::Instance().readFile(m_sPath+"/info.txt")).split("\n");

    QStringList listTempQuest = QString(Global::Instance().readFile(m_sPath+"/quest.txt")).split("\n");


    m_listInfo.clear();

    m_listQuest.clear();

    for(int i=0;i<listTempInfo.length();i++)
    {
        if(listTempInfo.at(i).trimmed()!="")
            m_listInfo.append(listTempInfo.at(i).trimmed());
    }

    for(int j=0;j<listTempQuest.length();j++)
    {
        if(listTempQuest.at(j).trimmed()!="")
            m_listQuest.append(listTempQuest.at(j).trimmed());
    }



    m_iChangeTime = qBound(3*1000,config("Base/changeTimer").toInt()*1000,60*60*1000);

    if(m_listInfo.length()>0)
    {
        b =true;

         m_iInfoIdx=0;

         ui->stackedWidget_5->setCurrentWidget(ui->pageInfo);

        ui->lbInfo->setText(m_listInfo.at(m_iInfoIdx));

        startTimer(m_iChangeTime);
    }

    return b;
}

void ItemTicket::resizeEvent(QResizeEvent *)
{
 //   int w = size().height()/2;

    //    ui->widget1->setMinimumSize(QSize(w,w));
    //    ui->widget1->setMaximumSize(QSize(w,w));


    //    ui->widget2->setMinimumSize(QSize(w,w));
    //    ui->widget2->setMaximumSize(QSize(w,w));

    //    ui->widget1->move(0,0);

    //    ui->widget2->move(0,w);

    ui->lb->setMinimumWidth(this->height());

}

void ItemTicket::mousePressEvent(QMouseEvent *)
{
    Global::Instance().setTouch();

    setQuest();

    setSelectButton();

}

void ItemTicket::timerEvent(QTimerEvent *)
{
    if(Global::Instance().isTouchLock() || Global::Instance().allStop())
        return ;

    m_iInfoIdx++;

    if(m_iInfoIdx>=m_listInfo.length())
        m_iInfoIdx=0;

    ui->stackedWidget_5->setCurrentWidget(ui->pageInfo);

    ui->lbInfo->setText(m_listInfo.at(m_iInfoIdx));


}

void ItemTicket::clickSelect()
{

}

void ItemTicket::setQuest()
{
    if(m_listQuest.length()<1)
        return ;


    ui->stackedWidget_5->setCurrentWidget(ui->pageSelect);

    if(m_iQuest>=m_listQuest.length() || m_iQuest<0 )
        m_iQuest=0;

     ui->lbQuest->setText(m_listQuest.at(m_iQuest));

    if(m_listQuest.length()<2)
    {
        ui->btnPreQeust->hide();

        ui->btnNextQuest->hide();
    }
    else
    {
        ui->btnPreQeust->setVisible(m_iQuest>0);

        ui->btnNextQuest->setVisible(m_iQuest<(m_listQuest.length()-1));

    }
}

void ItemTicket::setSelectButton()
{

     for(int i=0;i<m_listSelectBtn.length();i++)
     {
        QString sTarget = m_sPath+"/"+QString::number(m_iQuest+1)+"-"+
                QString::number(i+1)+".png";

        m_listSelectBtn[i]->hide();

        if(checkFile(sTarget))
        {

            QString sStyle = "border-image:url(\""+sTarget+"\");";

            m_listSelectBtn[i]->setStyleSheet(sStyle);
            m_listSelectBtn[i]->show();
        }

     }

}

bool ItemTicket::checkFile(QString sFile)
{

    return  QFileInfo(sFile).isFile();
}


void ItemTicket::on_btnPreQeust_clicked()
{
    if(m_iQuest==0)
        return ;

    m_iQuest--;

    setQuest();

    setSelectButton();
}

void ItemTicket::on_btnNextQuest_clicked()
{
    if(m_iQuest>=m_listQuest.length()-1)
        return ;

    m_iQuest++;

    setQuest();

    setSelectButton();
}
