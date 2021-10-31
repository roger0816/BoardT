#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentWidget(ui->stageManager);

    connect(ui->stageManager,&StageManager::sendSelectModel,this,&Widget::loadModel);

    connect(ui->stageEditArea,&StageEditArea::sendBack,this,&Widget::StageEditback);


    m_listButtonStack.addButton(ui->btnSetting,0);

    m_listButtonStack.addButton(ui->btnEdit,1);

    m_listButtonStack.addButton(ui->btnSchedule,2);

    m_listButtonStack.addButton(ui->btnTimeSchedule,3);


  //  QString sDef = QApplication::applicationDirPath()+"/data/model0";




//    connect(ui->wLayerSelector,&LayerSelector::sendSelectLayer,this,&Widget::slotSelector);

//    connect(ui->wLayerSelector,&LayerSelector::sendSelectLayer,ui->pageSchedule,&LayerSchedule::slotSelector);

//    connect(ui->wDisplay,&DisplayWidget::changeTarget,ui->wStyle,&LayerEditor::setTarget);

//    connect(ui->wDisplay,&DisplayWidget::changeTarget,ui->wAction,&LayerAction::setTarget);

//    connect(ui->wStyle,&LayerEditor::callUpdate,ui->wDisplay,&DisplayWidget::refreshItem);

//    connect(ui->wStyle,&LayerEditor::callRaise,ui->wDisplay,&DisplayWidget::raiseItem);

//    connect(ui->wStyle,&LayerEditor::callRename,this,&Widget::rename);

//    connect(ui->wStyle,&LayerEditor::callDelete,ui->wDisplay,&DisplayWidget::deleteItem);

//    connect(ui->wAdd,&LayerAddContent::btnAddClicked,ui->wDisplay,&DisplayWidget::addItem);

    ui->wStackWork->setCurrentWidget(ui->page0);

    ui->wTop->hide();

    ui->tabWidget->setCurrentWidget(ui->wStyle);

    qDebug()<<"widget create Ok";

}

Widget::~Widget()
{
    delete ui;
}

void Widget::loadModel(QString sPath)
{


    bool bHasModel = QDir().exists(sPath);

    if(bHasModel)
    {
        CDATA.readModel(sPath);

        ui->lbModel->setText(sPath.split("/").last());
    }
    else
    {

        CDATA.createModel(sPath);

        CDATA.readModel(sPath);

        qDebug()<<"model no found ,so create: "<<sPath;
    }




    ui->stackedWidget->setCurrentWidget(ui->stageEditArea);


}



void Widget::on_btnSelectModel_clicked()
{
    QString sPath = QFileDialog::getOpenFileName(this,"選擇模組",QApplication::applicationDirPath()+"/data","*.BDM");

    QStringList listTmp = sPath.split("/");

    listTmp.pop_back();


    loadModel(listTmp.join("/"));

}


void Widget::slotSelector(QString sName)
{



//    if(ui->btnEdit->isChecked())
//    {
//        ui->wStackWork->setCurrentWidget(ui->pageWork);

//        ui->wDisplay->setLayer(CDATA.m_sPath+"/"+sName);

//        ui->wDisplay->setEdit(true);

//    }
//    else if(ui->btnSetting->isChecked())
//    {
//        ui->wStackWork->setCurrentWidget(ui->pageSetting);
//    }

//    else if(ui->btnSchedule->isChecked())
//    {
//        ui->wStackWork->setCurrentWidget(ui->pageSchedule);
//    }

//    else if(ui->btnTimeSchedule->isChecked())
//    {
//        ui->wStackWork->setCurrentWidget(ui->pageTimeSchedule);


//        ui->pageTimeSchedule->setTimeData(sName);

//    }


}


void Widget::on_btnSave_clicked()
{
//    DialogMsg msg;

//    msg.setDialogInfo("確定要儲存嗎？",QStringList()<<"否"<<"是");

//    int iRe = msg.exec();

//    if(iRe == 1)
//    {

//        ui->pageSchedule->saveSchedule();

//        int iScheduleStatus = SCHEDULE_OFF;

//        if(ui->rdSchedule->isChecked())
//        {
//            iScheduleStatus = SCHEDULE_ON;
//        }
//        else if(ui->rdTimeSchedule->isChecked())
//        {
//            iScheduleStatus = SCHEDULE_TIME;
//        }

//        CDATA.m_dataModel.iScheduleMode = iScheduleStatus;


//        CDATA.writeModel(ui->wLayerSelector->m_sSetTargetPath);

//        QString sPath = CDATA.m_sPath;

//        QSettings conf(sPath+"/"+sPath.split("/").last()+".BDM",QSettings::IniFormat);

//        QDir dir(sPath);

//        // conf.setValue("Target",dir.path().split("/").last());

//        conf.setValue("DateTime",QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

//        conf.sync();


//        refreshSelector();
//    }
}



void Widget::on_btnUpload_clicked()
{
//    DialogMsg msg;

//    if(ui->lbModel->text().trimmed()=="")
//    {
//        msg.setDialogInfo("請先開啟模組",QStringList()<<"OK");

//        msg.exec();

//        return ;

//    }




//    msg.setInput("請輸入IP",m_sPreIp,QStringList()<<"取消"<<"確定");

//    int iRe = msg.exec();

//    if(iRe==1)
//    {
//        m_sPreIp = msg.getInput();

//        QString sPath = CDATA.m_sPath;

//        //     QSettings conf(sPath+"/conf.ini",QSettings::IniFormat);


//        QSettings conf(sPath+"/"+sPath.split("/").last()+".BDM",QSettings::IniFormat);


//        QDir dir(sPath);

//        // conf.setValue("Target",dir.path().split("/").last());

//        conf.setValue("DateTime",QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

//        conf.sync();


//        upload(m_sPreIp," -r "+sPath,"/home/pi/BoardT/bin/data/");

//    }
}

void Widget::upload(QString sIp, QString sTarget, QString sPath)
{
//    //putty.exe -ssh -l pi -pw pi -P 22 192.168.0.157 -m mvModel0.txt
//    QString sCmd =QApplication::applicationDirPath()+"/putty.exe -ssh -l pi -pw pi -P 22 "+sIp+" -m mvModel0.txt";

//    system(sCmd.toStdString().c_str());

//    sCmd = QApplication::applicationDirPath()+"/pscp.exe -P 22 -pw \"pi\" %2 pi@%1:%3";

//    sCmd = sCmd.arg(sIp).arg(sTarget).arg(sPath);

//    qDebug()<<"scmd : "<<sCmd;

//    system(sCmd.toStdString().c_str());



}

//void Widget::rename(QString sOld, QString sNew)
//{

//    CDATA.getObj(sOld)->m_sWaitRename = sOld;

//    ui->wDisplay->renameItem(sOld,sNew);


//}


void Widget::StageEditback()
{
    ui->stackedWidget->setCurrentWidget(ui->stageManager);
}

//void Widget::refreshTimeSchedule()
//{

//    if(m_bLockTimeSend)
//        return ;


//    if(CDATA.m_dData[ui->lbLayerNameForTime->text()] == nullptr)
//    return;
//    LayerData *layer =CDATA.m_dData.value(ui->lbLayerNameForTime->text());

//   layer->m_dataLayer.timeScheduleFrom =  ui->teFrom->time();

//   qDebug()<<layer->m_dataLayer.timeScheduleFrom;

//   layer->m_dataLayer.timeScheduleTo = ui->teTo->time();

//    layer->m_dataLayer.dayOfWeek = ui->cbTimeDayOfWeek->currentIndex();

//    layer->m_dataLayer.bStopPreVideo = ui->cbStopPreVideo->isChecked();
//  //  layerData->


//}




void Widget::on_btnTest_clicked()
{


    QString sApp = QApplication::applicationDirPath()+"/ActiveBoard.exe ";

    // QString sApp = QApplication::applicationDirPath()+"/ActiveTools.exe change ";
    //  system(sApp.toStdString().c_str());


    QProcess p;

    p.setWorkingDirectory(QApplication::applicationDirPath());

    p.startDetached(sApp);
    //p.start(sApp);
}



void Widget::on_btnTry_clicked()
{
    // QString sApp = QApplication::applicationDirPath()+"/ActiveBoard.exe ";

    QString sApp = QApplication::applicationDirPath()+"/ActiveTools.exe change "+ui->wLayerSelector->m_sSetTargetPath;
    system(sApp.toStdString().c_str());


    //QProcess p;

    //p.setWorkingDirectory(QApplication::applicationDirPath());

    //p.startDetached(sApp);
    //p.start(sApp);
}

void Widget::on_btnLayerBg_clicked()
{
    if(CDATA.m_sCurrentLayerName == "")
        return;

    QString sTarget =CDATA.m_sCurrentLayerName;

    if(CDATA.m_dData.keys().indexOf(sTarget)<0)
        return ;

    QString sPath = QFileDialog::getOpenFileName(this,"選擇版面背景圖",QApplication::applicationDirPath(),"*.png *.jpg *.jpeg");

    if(sPath != CDATA.m_dData[sTarget]->m_sBgPath)
    {
        CDATA.m_dData[sTarget]->m_sBgPath = sPath;

        ui->wDisplay->refreshItem();
    }
}

void Widget::on_btnDelLayerBg_clicked()
{
    if(CDATA.m_sCurrentLayerName == "")
        return;

    QString sTarget =CDATA.m_sCurrentLayerName;

    if(CDATA.m_dData.keys().indexOf(sTarget)<0)
        return ;


    if(CDATA.m_dData[sTarget]->m_sBgPath != "")
    {
        CDATA.m_dData[sTarget]->m_sBgPath = "";

        ui->wDisplay->refreshItem();
    }
}

void Widget::on_btnEdit_clicked()
{
    if(ui->wLayerSelector->m_sCurrentPath=="")
        ui->wStackWork->setCurrentWidget(ui->page0);
    else
    {
        ui->wStackWork->setCurrentWidget(ui->pageWork);

    }

}

void Widget::on_btnSetting_clicked()
{
    int iStatus = CDATA.m_dataModel.iScheduleMode;

    ui->rdNoneSchedule->setChecked(false);

    ui->rdSchedule->setChecked(false);

    ui->rdTimeSchedule->setChecked(false);


    if(iStatus==SCHEDULE_TIME)
    {
        ui->rdTimeSchedule->setChecked(true);
    }

    else if(iStatus==SCHEDULE_ON)
    {
        ui->rdSchedule->setChecked(true);
    }
    else
        ui->rdNoneSchedule->setChecked(true);



    ui->wStackWork->setCurrentWidget(ui->pageSetting);
}

void Widget::on_btnSchedule_clicked()
{
    ui->wStackWork->setCurrentWidget(ui->pageSchedule);
}

void Widget::on_btnTimeSchedule_clicked()
{

    qDebug()<<ui->wLayerSelector->m_sCurrentPath;


    if(ui->wLayerSelector->m_sCurrentPath=="")
        ui->wStackWork->setCurrentWidget(ui->page0);
    else
    {
        ui->wStackWork->setCurrentWidget(ui->pageTimeSchedule);

        QString sLayerName = ui->wLayerSelector->m_sCurrentPath.split("/").last();

        ui->pageTimeSchedule->setTimeData(sLayerName);

    }
}





void Widget::on_rdNoneSchedule_clicked()
{
    // CDATA.m_dData
}

void Widget::on_rdSchedule_clicked()
{

}

void Widget::on_rdTimeSchedule_clicked()
{

}




void Widget::on_btnUploadUsb_clicked()
{
    DialogUploadUsb dialog;

    dialog.resize(size()*0.6);

    int re = dialog.exec();

    if(re == 1)
    {
        QString sTarget = dialog.m_sPath;

        // conf.setValue("Target",dir.path().split("/").last());

        QString sPath = CDATA.m_sPath;

        QSettings conf(sPath+"/"+sPath.split("/").last()+".BDM",QSettings::IniFormat);

        QDir dir(sPath);


        conf.setValue("DateTime",QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

        conf.sync();

        //   upload(m_sPreIp," -r "+sPath,"/home/pi/BoardT/bin/data/");

        auto checkDir = [=](QString sDir)
        {
            if(!QDir(sDir).exists())
            {
                QDir().mkdir(sDir);
            }
        };


        checkDir(sTarget+"/BoardT");

        checkDir(sTarget+"/BoardT/bin");

        checkDir(sTarget+"/BoardT/bin/data");

        QString sCmd = "scp -r "+sPath+" "+sTarget+"/BoardT/bin/data";

        system(sCmd.toStdString().c_str());

    }
}

