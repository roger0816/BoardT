#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    if(Global::Instance().m_dialogPop ==nullptr)
        Global::Instance().m_dialogPop = new DialogPop(ui->wBg);

    connect(Global::Instance().m_dialogPop,&DialogPop::sendTouchLock,
            &Global::Instance(),&Global::setTouch);

    Global::Instance().m_dialogPop->move(0,0);

    Global::Instance().m_dialogPop->hide();


    connect(&Global::Instance().m_usb,&FuncUsb::usbChange,
            this,&Widget::usbChange);



    QSettings conf(QApplication::applicationDirPath()+"/../bin/data/layer/conf.ini",QSettings::IniFormat);

    m_sCurrentBoard =conf.value("Target").toString();

    m_sCurrentVerDateTime = conf.value("DateTime").toString();


    connect(&m_timer,&QTimer::timeout,this,&Widget::slotTimer);

    QTimer::singleShot(3000,this,SLOT(loadingLicense()));




}

Widget::~Widget()
{


    Global::Instance().destory();

    delete ui;
}

void Widget::loadConfig(QString sLayer)
{

    if(sLayer=="")
        return;
    QString sPath = QApplication::applicationDirPath()+"/../bin/data/layer/"+sLayer;
      qDebug()<<"loading layer : "<<sLayer;
    QSettings defin(RDATA+"/layer/define.ini",QSettings::IniFormat);

    m_dDefine.clear();

    QStringList listDefineKey= defin.allKeys();

    for(int i=0; i < listDefineKey.length();i++)
    {
        QString sKey = listDefineKey.at(i);

        int iValue = defin.value(sKey).toInt();

        m_dDefine.insert(sKey,iValue);
    }




    if(m_sTestModel!="")
        sPath = sLayer;

    QSettings setting(sPath+"/"+sLayer.split("/").last()+".BDT",QSettings::IniFormat);

    qDebug()<<"sPath : "<<sPath;

    Global::Instance().m_iResumeSec = setting.value("Base/resumeTimer").toInt()*1000;



    Global::Instance().m_fDiffSize = float(qApp->desktop()->height())/1920;



    QFileInfoList listDir = QDir(sPath).entryInfoList(QDir::AllDirs);

    qDebug()<<"all content : "<<listDir.toStdList();

    ui->wBg->setObjectName("main_bg");
    ui->wBg->setStyleSheet("QWidget#main_bg{border-image:url("+sPath+"/bg.png);}");

    m_listDir.clear();

    qDebug()<<"AA0";

    foreach(LayerContent *item,m_listContent)
    {
        item->hide();
    }

    qDebug()<<"AA1" <<listDir.length();

    int iLen = m_listContent.length();

    for(int i=0;i<listDir.length();i++)
    {
        qDebug()<<"AA1a : "<<i;
        qDebug()<<"AA1b : "<<m_listContent.length();
        QFileInfo dir = listDir.at(i);

        if(dir.fileName()!="." && dir.fileName()!="..")
        {
            m_listDir.append(dir);

            while(iLen<=i)
            {
                m_listContent.append(new LayerContent(ui->wBg));

                m_listContent.last()->hide();

                iLen++;

            }


            qDebug()<<"aa1c :"<<m_listContent.length()<<" i : "<<i;
            m_listContent[i]->setPath(dir.filePath(),m_dDefine);

            //  m_listContent[i]->show();
        }
    }


    qDebug()<<"AA2";

    Global::Instance().m_dialogPop->setBg(sPath+"/popBg.png");

    Global::Instance().m_dialogPop->raise();

    Global::Instance().m_dialogPop->hide();


}

void Widget::loadingLicense()
{
    ui->lbLicense->hide();

    ui->lbUsbKey->hide();

    ui->lbLoginKey->hide();



    if(Global::Instance().m_usb.isReg())
    {

        if(Global::Instance().m_usb.isLogin())
        {


            launch();
        }
        else
        {

            ui->wFactory->setVisible(Global::Instance().m_usb.isDevelop());

            ui->stack->setCurrentWidget(ui->wLogin);

        }
    }
    else
    {


        ui->stack->setCurrentWidget(ui->wReg);

    }


}

void Widget::resizeEvent(QResizeEvent *)
{

    Global::Instance().m_dialogPop->resize(width(),height()/2+170);


    Global::Instance().m_dialogPop->move(0,height()/2-170);


    Global::Instance().m_fDiffSize = float(height())/1920;


}

void Widget::slotTimer()
{
    QSettings conf(QApplication::applicationDirPath()+"/../bin/data/layer/conf.ini",QSettings::IniFormat);

    QString board =conf.value("Target").toString();

    QString sTime = conf.value("DateTime").toString();

    if(board!=m_sCurrentBoard || sTime != m_sCurrentVerDateTime)
    {
        m_sCurrentBoard = board;

        m_sCurrentVerDateTime = sTime;

        launch();
    }

}



void Widget::launch(int iIdx)
{
    ui->stack->setCurrentWidget(ui->wBg);


    if(m_sTestModel!="")
    {
        loadConfig(m_sTestModel);
        return ;
    }

  //  if(iIdx==0)

    m_timer.stop();

    m_timer.start(3000);


    loadConfig(m_sCurrentBoard);


}

void Widget::refresh()
{
    loadConfig(m_sCurrentBoard);

}

void Widget::usbChange(QString sUuid, QString sPath, bool bPlugIn)
{
    bool bDev = Global::Instance().m_usb.isDevelop();

    bool bDiff = Global::Instance().m_usb.differentDevUsb(sUuid);


    if(ui->stack->currentWidget()==ui->wReg)
    {


        if(!bDiff)
        {
            ui->lbLicense->setVisible(bPlugIn);
        }
        else
        {

            ui->lbUsbKey->setVisible(bPlugIn);

            m_sRegUuid="";

            if(bPlugIn)
                m_sRegUuid = sUuid;

        }

        ui->btn->setEnabled(ui->lbLicense->isVisible() && ui->lbUsbKey->isVisible());

    }

    else if(ui->stack->currentWidget()==ui->wLogin)
    {
        if(!bDiff)
        {
            ui->wFactory->setVisible(bPlugIn);
        }
        else
        {
            if(bPlugIn && Global::Instance().m_usb.isLogin(sUuid))
            {
                ui->lbLoginKey->show();

                QTimer::singleShot(500,this,SLOT(launch()));
            }
        }



    }

    else if(ui->stack->currentWidget()==ui->wBg)
    {
        if(bPlugIn)
        {
            if(Global::Instance().m_usb.isDevelop(sUuid) ||
                    Global::Instance().m_usb.isLogin(sUuid))
            {
                ui->stack->setCurrentWidget(ui->wSys);
            }

        }

    }
    else if(ui->stack->currentWidget()==ui->wSys)
    {
        if(!bPlugIn)
        {
            if(Global::Instance().m_usb.isDevelop(sUuid) ||
                    Global::Instance().m_usb.isLogin(sUuid))
            {
                ui->stack->setCurrentWidget(ui->wBg);
            }


        }


    }


}

void Widget::on_btn_clicked()
{
    Global::Instance().m_usb.writeReg(m_sRegUuid);

    launch();
}

void Widget::on_btnReReg_clicked()
{
    Global::Instance().m_usb.removeReg();

    loadingLicense();
}

void Widget::on_btnFacLogin_clicked()
{
    launch();
}

void Widget::on_btnUpdateData_clicked()
{
    QString sUpdatePath = Global::Instance().m_usb.m_sLastUsbPath+"/ActiveBoard/data/";

    qDebug()<<" update Path : "<<sUpdatePath;
    QString sCurrentPath = QApplication::applicationDirPath()+"/../bin/data/";

    qDebug()<<" current path :"<<sCurrentPath;

    QString sCmd = "cp -r "+sUpdatePath+"layer "+sCurrentPath+"layerNew";

    qDebug()<<"cmd : "<<sCmd;

    system(sCmd.toStdString().c_str());

    QString sCmdRemove = "rm -rf "+sCurrentPath+"layer";

    qDebug()<<"cmd : "<<sCmdRemove;
    system(sCmdRemove.toStdString().c_str());

    QString sCmdRename = "mv "+sCurrentPath+"layerNew "+sCurrentPath+"layer";

    qDebug()<<"cmd : "<<sCmdRename;
    system(sCmdRename.toStdString().c_str());


    launch();


}


void Widget::on_btnUpdateSys_clicked()
{
    QString sUpdatePath = Global::Instance().m_usb.m_sLastUsbPath+"/ActiveBoard/bin/";

    QString sCurrentPath = QApplication::applicationDirPath()+"/../bin/";

    QString sCmd = "cp -r "+sUpdatePath+"ActiveBoard "+sCurrentPath+"ActiveBoardNew";

    qDebug()<<"cmd : "<<sCmd;

    system(sCmd.toStdString().c_str());

    system("reboot");


}

void Widget::on_btnBack_clicked()
{
       launch();
}

void Widget::on_btnReboot_clicked()
{
     system("reboot");
}
