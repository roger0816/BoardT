#include "LayerContent.h"
#include "ui_LayerContent.h"

LayerContent::LayerContent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerContent)
{
    ui->setupUi(this);



}

LayerContent::~LayerContent()
{
    delete ui;
}

void LayerContent::setPath(QString sPath,QMap<QString,int> typeMapping)
{
    qDebug()<<"path : "<<sPath;
    QSettings conf(sPath+"/conf.ini",   QSettings::IniFormat);

    int iType = conf.value("Base/type").toInt();
    qDebug()<<" iType "<<iType;

    qDebug()<<typeMapping;
    QString sType = typeMapping.key(conf.value("Base/type").toInt());
    qDebug()<<"stype : "<<sType;
    int iX = conf.value("Base/x").toInt();

    int iY = conf.value("Base/y").toInt();

    int iW = conf.value("Base/w").toInt();

    int iH = conf.value("Base/h").toInt();


    bool bHasDefine = true ;

    if(sType==TYPE.TEXT)
    {


        // this->setStyleSheet("background-color:rgba(0,255,255,255);");

        ui->stackedWidget->setStyleSheet("background-color:rgba(255,255,0,0);");


        ui->wTxt->setPath(sPath);

        ui->stackedWidget->setCurrentWidget(ui->wTxt);

    }
    else if(sType==TYPE.PIC)
    {
        QFileInfoList list = QDir(sPath).entryInfoList(QStringList()<<"*.png"<<".jpg"<<"*.PNG"<<"*.JPG");


        if(list.length()>0)
        {

            ui->wPic->setPath(sPath);

            ui->stackedWidget->setCurrentWidget(ui->wPic);
        }

    }


    else if(sType==TYPE.BUTTON)
    {


        // this->setStyleSheet("background-color:rgba(0,255,255,255);");

        // ui->stackedWidget->setStyleSheet("background-color:rgba(255,255,0,0);");


        ui->wBtn->setPath(sPath);

        ui->stackedWidget->setCurrentWidget(ui->wBtn);

    }

    else if(sType==TYPE.WEB_VIEW)
    {

        ui->wWeb->setPath(sPath);

        ui->stackedWidget->setCurrentWidget(ui->wWeb);

    }

    else if(sType==TYPE.DATE_TIME)
    {
        ui->wDateTime->setPath(sPath);

        ui->stackedWidget->setCurrentWidget(ui->wDateTime);

    }

    else if(sType==TYPE.FUNCTION)
    {
        ui->wFunction->setPath(sPath);

        ui->stackedWidget->setCurrentWidget(ui->wFunction);

    }

    else if(sType==TYPE.VIDEO)
    {

        if(m_mdeia!=nullptr)
            m_mdeia->hide();

        if(m_video==nullptr)
        {
            m_video = new ItemVideo(ui->wVideo);


            connect(&Global::Instance(),&Global::callPlay,m_video,&ItemVideo::setPlayAdnPause);

        }

        m_video->show();

        m_video->setPath(sPath);

        ui->stackedWidget->setCurrentWidget(ui->wVideo);

    }

    //

    else if(sType==TYPE.LOGO)
    {
        QFileInfoList list = QDir(sPath).entryInfoList(QStringList()<<"*.png"<<".jpg"<<"*.PNG"<<"*.JPG");

        if(list.length()>0)
        {

            ui->wPic->setPath(sPath);

            ui->stackedWidget->setCurrentWidget(ui->wPic);
        }

    }


    else if(sType==TYPE.MEDIA_CENT)
    {
        qDebug()<<"BB0 :";
        if(m_video!=nullptr)
            m_video->hide();

              qDebug()<<"BB1 :";

        if(m_mdeia==nullptr)
        {
            m_mdeia = new ItemMediaCent(ui->wVideo);

            connect(ui->wFunction,&ItemFunction::sendPlay,m_mdeia->m_player,&CPlayer::setPlayAdnPause);

        }

              qDebug()<<"BB2 :";

        m_mdeia->show();

        m_mdeia->setPath(sPath);

              qDebug()<<"BB3 :";

        ui->stackedWidget->setCurrentWidget(ui->wVideo);

    }

    else if(sType==TYPE.TICKET)
    {
        ui->wTicket->setPath(sPath);

        ui->stackedWidget->setCurrentWidget(ui->wTicket);

    }

    else if(sType==TYPE.ACTIVE)
    {

        ui->wAction->setPath(sPath);

        ui->stackedWidget->setCurrentWidget(ui->wAction);

    }

    else if(sType==TYPE.ON_SALE)
    {

        ui->wPicRun->setPath(sPath);

        ui->stackedWidget->setCurrentWidget(ui->wPicRun);

    }


    else
    {
        bHasDefine = false;
    }



    m_sType =sType;


    float iScale =Global::Instance().m_fDiffSize;

    qDebug()<<"scale : "<<iScale;

    setMaximumSize(iW*iScale,iH*iScale);

    setMinimumSize(iW*iScale,iH*iScale);

    move(iX*iScale,iY*iScale);


    if(bHasDefine)
        setVisible(iW!=0 && iH!=0);





}

void LayerContent::resizeEvent(QResizeEvent *)
{
    if(m_mdeia!=nullptr)
        m_mdeia->resize(ui->wVideo->size());

    if(m_video!=nullptr)
        m_video->resize(ui->wVideo->size());
}

void LayerContent::showEvent(QShowEvent *)
{
    if(m_mdeia!=nullptr)
        m_mdeia->resize(ui->wVideo->size());

    if(m_video!=nullptr)
        m_video->resize(ui->wVideo->size());
}

void LayerContent::checkLayout(int &iX, int &iY, int &iW, int &iH)
{
    if(!Global::Instance().m_bAutoLayout)
        return ;

    QSize rSize(480,800);

    //rSize= qApp->desktop()->size();

    qDebug()<<"rsize : "<<rSize;

    float diff= (float)rSize.width()/1080;

   // float diffH = (float)rSize.height()/1920;

    iX=iX*diff;

    iY=iY*diff;

    iW=iW*diff;

    iH=iH*diff;
    qDebug()<<"diffW : "<<diff;

}

void LayerContent::stopVideo()
{
//    if(m_mdeia != nullptr)
//        m_mdeia->st
}
