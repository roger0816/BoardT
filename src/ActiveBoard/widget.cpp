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



    QSettings conf(QApplication::applicationDirPath()+"/../bin/data/model0/model0.BDM",QSettings::IniFormat);

    m_sCurrentBoard =conf.value("Target").toString();

    m_sCurrentVerDateTime = conf.value("DateTime").toString();


    connect(&m_timer,&QTimer::timeout,this,&Widget::slotTimer);


    int iPin = 27;

    QString sTmp ="echo "+QString::number(iPin)+" > /sys/class/gpio/export ";


    system(sTmp.toStdString().c_str());


    QString sTmp2 ="echo low > /sys/class/gpio/gpio"+QString::number(iPin)+"/direction";

    system(sTmp2.toStdString().c_str());

    connect(&m_timerWaitLogin,&QTimer::timeout,this,&Widget::slotWaitLogin);
    // ui->wDisplay->setMinimumSize(1080,1920);

    QTimer::singleShot(1000,this,SLOT(loadingLicense()));


    m_listUsbUpdate = new LayerUsbUpdate(this);

    m_listUsbUpdate->hide();


#ifndef WIN32
    m_udev = new UdevMonitor;

    connect(m_udev,SIGNAL(deviceAdded(QString)),this,SLOT(slotUsbAdd(QString )));

    connect(m_udev,SIGNAL(deviceRemoved(QString)),this,SLOT(slotUsbRemove(QString )));

    m_udev->start();

#endif

}

Widget::~Widget()
{


    Global::Instance().destory();

    delete ui;
}

void Widget::loadConfig(QString sLayer)
{

    if(m_wDisplay == nullptr)
    {
        m_wDisplay = new DisplayWidget(ui->wBg);

        connect(&CCTRL,&CCtrlFunc::callChangePage,m_wDisplay,&DisplayWidget::slotChangeLayer);

    }
 //   CCTRL.setCtrlSource(&CDATA,m_wDisplay);

    m_wDisplay->show();

    m_wDisplay->resize(ui->wBg->size());

    CDATA.readModel(QApplication::applicationDirPath()+"/../bin/data/model0");

    m_wDisplay->setLayer(sLayer,m_iVideoStatus);

    m_wDisplay->setEdit(false);

    ui->stack->setCurrentWidget(ui->wBg);

    return ;

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


    ui->wBg->setObjectName("main_bg");
    ui->wBg->setStyleSheet("QWidget#main_bg{border-image:url("+sPath+"/bg.png);}");

    m_listDir.clear();


    foreach(LayerContent *item,m_listContent)
    {
        item->hide();
    }


    int iLen = m_listContent.length();

    for(int i=0;i<listDir.length();i++)
    {

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


            m_listContent[i]->setPath(dir.filePath(),m_dDefine);

            //  m_listContent[i]->show();
        }
    }



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

            m_iWaitTimeout = 10;

            ui->lbUpdateData->hide();

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

void Widget::showEvent(QShowEvent *)
{
    if(m_wDisplay!=nullptr)
        m_wDisplay->resize(size());

    checkIpAndName();
}

void Widget::checkIpAndName()
{

    m_sIp="";

    QList<QHostAddress> list = QNetworkInterface::allAddresses();

    for(int i=0;i<list.length();i++)
    {
        if(list.at(i) != QHostAddress::LocalHost && list.at(i).toIPv4Address())
        {
            m_sIp = list.at(i).toString();
            break;
        }
    }

    if(m_sIp=="")
    {
        m_sIp = QHostAddress(QHostAddress::LocalHost).toString();
    }




#ifdef Q_OS_WINDOWS
    m_sDeviceName="Test";
#else
    QString sPath = QApplication::applicationDirPath()+"/../../deviceInfo";

    QFile file(sPath);

    if(file.open(QIODevice::ReadWrite))
    {
        m_sDeviceName = QString(file.readAll()).split("\n").first().trimmed();

        file.close();
    }

#endif

    ui->lbName->setText(m_sDeviceName);

    ui->lbName2->setText(m_sDeviceName);



    if(m_sIp=="127.0.0.1" || m_sIp=="")
    {
        m_sIp = "";
        QTimer::singleShot(3000,this,SLOT(checkIpAndName()));
    }

    ui->lbIp->setText(m_sIp);

    ui->lbIp2->setText(m_sIp);

}

void Widget::slotUsbAdd(QString)
{

#ifndef WIN32
    m_listUsb = m_udev->deviceList();
    m_listUsbUpdate->setUsbList(m_listUsb);
#endif

}

void Widget::slotUsbRemove(QString)
{
#ifndef WIN32
    m_listUsb = m_udev->deviceList();
    m_listUsbUpdate->setUsbList(m_listUsb);
#endif
}


void Widget::mousePressEvent(QMouseEvent *e)
{
    if(e->pos().x()> width()-50 && e->pos().y()> height()-50)
    {
        m_bIsPress = true;
    }
    else
    {
        m_bIsPress = false;

        m_iPressTime = 0;

    }

    // ui->wDisplay->setEdit(false);
}

void Widget::mouseReleaseEvent(QMouseEvent *e)
{
    m_bIsPress = false;

    m_iPressTime =0;
}

void Widget::slotTimer()
{

    if(m_bIsPress)
    {
        m_iPressTime++;

        if(m_iPressTime>5)
        {
            //           if(m_wDisplay!=nullptr)
            //            m_wDisplay->setEdit(true);

            m_iPressTime = 0;
        }
    }


    if(QDir().exists("/sys/class/gpio/"))
    {
        QProcess p;

        p.start("cat",QStringList()<<"/sys/class/gpio/gpio27/value");

        p.waitForFinished();

        QString st(p.readAll());

        if(st.mid(0,1) == "1")
        {

//            ui->lbUpdateData->show();

//            // m_timerWaitLogin.stop();

//            on_btnUpdateData_clicked();

//            QTimer::singleShot(3000,ui->lbUpdateData,SLOT(hide()));


            m_listUsbUpdate->resize(this->width(),this->height());

            m_listUsbUpdate->raise();

            m_listUsbUpdate->show();


        }
        else
        {
                m_listUsbUpdate->hide();
        }
    }




    //    QSettings conf(QApplication::applicationDirPath()+"/../bin/data/model0/conf.ini",QSettings::IniFormat);
    QSettings conf(QApplication::applicationDirPath()+"/../bin/data/model0/model0.BDM",QSettings::IniFormat);

    QString board =conf.value("Target").toString();

    QString sTime = conf.value("DateTime").toString();

    m_iVideoStatus = conf.value("VideoStatus").toInt();

    if(board!=m_sCurrentBoard || sTime != m_sCurrentVerDateTime)
    {
        m_sCurrentBoard = board;

        m_sCurrentVerDateTime = sTime;
        qDebug()<<"change board :  "<<m_sCurrentBoard;
        launch();
    }

}

void Widget::slotWaitLogin()
{
    m_iWaitTimeout--;

    if(m_iWaitTimeout<=0)
    {
        m_timerWaitLogin.stop();

        launch();

    }

    else
    {
        if(QDir().exists("/sys/class/gpio/"))
        {
            QProcess p;

            p.start("cat",QStringList()<<"/sys/class/gpio/gpio27/value");

            p.waitForFinished();

            QString st(p.readAll());

            if(st.mid(0,1) == "1")
            {
                ui->lbUpdateData->show();

                // m_timerWaitLogin.stop();

                on_btnUpdateData_clicked();

                QTimer::singleShot(3000,ui->lbUpdateData,SLOT(hide()));
            }
        }

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

    m_timer.start(1000);


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


                //  m_timerWaitLogin.start(300);

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


    QString sUpdatePath = Global::Instance().m_usb.m_sLastUsbPath+"/BoardT/bin/data/model0";
    qDebug()<<"AAAAAX : on_btnUpdateData_clicked"<<sUpdatePath;

    if(m_bLocker || Global::Instance().m_usb.m_sLastUsbPath.trimmed()=="")
    {
        return ;
    }

    m_bLocker = true;

    qDebug()<<"AAAAA0 : on_btnUpdateData_clicked";

    QString sCmd = "nohup ./updateFromUsb.sh "+sUpdatePath;

    system("chmod a+x updateFromUsb.sh > updateUsb.log 2>&1 &");

    system(sCmd.toStdString().c_str());


    //    qDebug()<<" update Path : "<<sUpdatePath;
    //    QString sCurrentPath = QApplication::applicationDirPath()+"/data/";

    //    QString rmCmd = "rm -rf "+sCurrentPath+"model0BK";

    //    system(rmCmd.toStdString().c_str());

    //    QString sBkCmd = "mv "+sCurrentPath+"model0 "+sCurrentPath+"model0BK";

    //    system(sBkCmd.toStdString().c_str());

    //    QString sCopy = "cp -r "+sUpdatePath+" "+sCurrentPath;


    //    system(sCopy.toStdString().c_str());

    //    launch();


}


void Widget::on_btnUpdateSys_clicked()
{
    QString sFile =QApplication::applicationDirPath()+"/cmd/updateFw.sh";

    QString sCmd = "chmod a+x "+sFile;

    system(sCmd.toStdString().c_str());

    sCmd = "./"+sFile;

    system(sCmd.toStdString().c_str());



    //    QString sUpdatePath = Global::Instance().m_usb.m_sLastUsbPath+"/ActiveBoard/bin/";

    //    QString sCurrentPath = QApplication::applicationDirPath()+"/../bin/";

    //    QString sCmd = "cp -r "+sUpdatePath+"ActiveBoard "+sCurrentPath+"ActiveBoardNew";

    //    qDebug()<<"cmd : "<<sCmd;

    //    system(sCmd.toStdString().c_str());

    //    system("reboot");


}

void Widget::on_btnBack_clicked()
{
    launch();
}

void Widget::on_btnReboot_clicked()
{
    system("reboot");
}
