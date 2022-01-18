#include "StageEditArea.h"
#include "ui_StageEditArea.h"

StageEditArea::StageEditArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageEditArea)
{
    ui->setupUi(this);


    connect(ui->wLayerSelector,&LayerSelector::sendSelectLayer,this,&StageEditArea::slotSelector);


    connect(ui->wDisplay,&DisplayWidget::changeTarget,ui->wStyle,&LayerEditor::setTarget);

    connect(ui->wDisplay,&DisplayWidget::changeTarget,ui->wAction,&LayerAction::setTarget);

    connect(ui->wStyle,&LayerEditor::callUpdate,ui->wDisplay,&DisplayWidget::refreshItem);

    connect(ui->wStyle,&LayerEditor::callRaise,ui->wDisplay,&DisplayWidget::raiseItem);

    connect(ui->wStyle,&LayerEditor::callRename,ui->wDisplay,&DisplayWidget::renameItem);

    connect(ui->wStyle,&LayerEditor::callDelete,ui->wDisplay,&DisplayWidget::deleteItem);

    connect(ui->wAdd,&LayerAddContent::btnAddClicked,ui->wDisplay,&DisplayWidget::addItem);

    connect(&CCTRL,&CCtrlFunc::callChangePage,ui->wDisplay,&DisplayWidget::slotChangeLayer);

    ui->wStackWork->setCurrentWidget(ui->pageWork);
    ui->wBottom->setCurrentWidget(ui->wBottomPage1);
}

StageEditArea::~StageEditArea()
{
    delete ui;
}

void StageEditArea::on_btnAddLayer_clicked()
{

        LayerNewModel newLay;

        newLay.setPath("新增版型",CDATA.m_sPath);

        int iRe = newLay.exec();

        if(iRe ==1 )
        {
            QString defLayer = newLay.m_sModelPath;

            CDATA.addLayer(defLayer);

            refreshSelector();
        }

}

void StageEditArea::on_btnRemoveLayer_clicked()
{
    DialogMsg msg;

    QString sPath = ui->wLayerSelector->m_sCurrentPath;

    QString sTarget = sPath.split("/").last();

    if(sTarget==DEF_LAYER_NAME)
    {
        msg.setDialogInfo("預設樣版無法刪除，請選擇其它",QStringList()<<"ok");

        msg.exec();

        return;
    }

    else if(sTarget=="")
    {
        msg.setDialogInfo("請先選擇要刪除的樣版",QStringList()<<"ok");

        msg.exec();

        return;
    }

    QString sTmp ="確定要刪除' %1 '嗎？";

    msg.setDialogInfo(sTmp.arg(sTarget),QStringList()<<"否"<<"是");

    int iRe = msg.exec();

    if(iRe == 1)
    {
        CDATA.removeLayer(sPath);

        refreshSelector(true);


    }
}

void StageEditArea::refreshSelector(bool bToDef)
{
    qDebug()<<"re selector";

    QStringList listKey = CDATA.m_dData.keys();

    qDebug()<<"listkey "<<listKey;

    qDebug()<<CDATA.m_dData;

    DisplayWidget w;

    QMap <QString , QPixmap> dPix;

    for(int i=0;i<listKey.length();i++)
    {

        dPix.insert(listKey[i], w.setLayer(CDATA.m_dData[listKey.at(i)]->m_sLayerPath));

    }

    ui->wLayerSelector->setData(dPix,CDATA.m_sPath);

    if(bToDef)
    {
        ui->wLayerSelector->toDef();
    }
}

void StageEditArea::showEvent(QShowEvent *)
{
    qDebug()<<"show event : StageEditArea";

    ui->btnBack->setMaximumWidth(54);
    refreshSelector();
}

void StageEditArea::on_btnBack_clicked()
{
    if(ui->wStackWork->currentWidget()==ui->pageWork)
        emit sendBack();
    else if(ui->wStackWork->currentWidget()==ui->pageSchedule)
    {
        changePage(0);
    }
}

void StageEditArea::on_btnSave_clicked()
{
    DialogMsg msg;

    msg.setDialogInfo("確定要儲存嗎？",QStringList()<<"否"<<"是");

    int iRe = msg.exec();

    if(iRe == 1)
    {

        int iScheduleStatus = SCHEDULE_OFF;

        CDATA.m_dataModel.iScheduleMode = iScheduleStatus;


        CDATA.writeModel(ui->wLayerSelector->m_sSetTargetPath);

        QString sPath = CDATA.m_sPath;

        QSettings conf(sPath+"/model0.BDM",QSettings::IniFormat);

        QDir dir(sPath);

        // conf.setValue("Target",dir.path().split("/").last());

        conf.setValue("DateTime",QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

        conf.sync();


        refreshSelector();
    }
}

void StageEditArea::on_btnUpload_clicked()
{

    changePage(1);
return;


    auto fnSave =[=]()
    {
        int iScheduleStatus = SCHEDULE_OFF;

        CDATA.m_dataModel.iScheduleMode = iScheduleStatus;


        CDATA.writeModel(ui->wLayerSelector->m_sSetTargetPath);

        QString sPath = CDATA.m_sPath;

        QSettings conf(sPath+"/model0.BDM",QSettings::IniFormat);

        QDir dir(sPath);

        // conf.setValue("Target",dir.path().split("/").last());

        conf.setValue("DateTime",QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

        conf.sync();


        refreshSelector();
    };


    auto fnUpload =[=](QString sIp,QString sTarget,QString sPath)
    {
        QString sCmd =QApplication::applicationDirPath()+"/putty.exe -ssh -l pi -pw pi -P 22 "+sIp+" -m mvModel0.txt";

        system(sCmd.toStdString().c_str());

        sCmd = QApplication::applicationDirPath()+"/pscp.exe -P 22 -pw \"pi\" %2 pi@%1:%3";

        sCmd = sCmd.arg(sIp).arg(sTarget).arg(sPath);

        qDebug()<<"scmd : "<<sCmd;

        system(sCmd.toStdString().c_str());

    };



    DialogMsg msg;

    msg.setInput("請輸入IP",m_sPreIp,QStringList()<<"取消"<<"確定");

    int iRe = msg.exec();

    if(iRe==1)
    {
        m_sPreIp = msg.getInput();

        QString sPath = CDATA.m_sPath;

        //     QSettings conf(sPath+"/conf.ini",QSettings::IniFormat);


        QSettings conf(sPath+"/model0.BDM",QSettings::IniFormat);


        QDir dir(sPath);

        // conf.setValue("Target",dir.path().split("/").last());

        conf.setValue("DateTime",QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

        conf.sync();


        fnSave();

        fnUpload(m_sPreIp," -r "+sPath,"/home/pi/BoardT/bin/data/");

    }
}

void StageEditArea::on_btnView_clicked()
{
    QString sApp = QApplication::applicationDirPath()+"/ActiveBoard.exe ";

    // QString sApp = QApplication::applicationDirPath()+"/ActiveTools.exe change ";
    //  system(sApp.toStdString().c_str());


    QProcess p;

    p.setWorkingDirectory(QApplication::applicationDirPath());

    p.startDetached(sApp);
}

void StageEditArea::slotSelector(QString sName)
{
    CDATA.m_dataModel.sTarget = sName;

    ui->wStackWork->setCurrentWidget(ui->pageWork);

    ui->wDisplay->setLayer(CDATA.m_sPath+"/"+sName);

    ui->wDisplay->setEdit(true);
}


void StageEditArea::on_btnLayerBg_clicked()
{

    if(CDATA.m_sCurrentLayerName == "")
        return;

    QString sTarget =CDATA.m_sCurrentLayerName;

    if(CDATA.m_dData.keys().indexOf(sTarget)<0)
        return ;

    QString sPath = QFileDialog::getOpenFileName(this,"選擇版面背景圖",QApplication::applicationDirPath(),"*.png *.jpg *.jpeg");

    if(sPath!="" &&  sPath != CDATA.m_dData[sTarget]->m_sBgPath)
    {
        CDATA.m_dData[sTarget]->m_sBgPath = sPath;

        ui->wDisplay->refreshItem();
    }
}

void StageEditArea::on_btnDelLayerBg_clicked()
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

void StageEditArea::changePage(int iIdx)
{
    if(iIdx==0) //page work
    {
        ui->wStackWork->setCurrentWidget(ui->pageWork);

        ui->wBottom->setCurrentWidget(ui->wBottomPage1);

        ui->wLayerSelector->setReadOnly(false);
    }
    else
    {
        ui->wStackWork->setCurrentWidget(ui->pageSchedule);

        ui->wBottom->setCurrentWidget(ui->wBottomPage2);

        ui->wLayerSelector->setReadOnly(true);

    }
}

void StageEditArea::on_btnToNet_clicked()
{

    DialogUploadNet dialog;

    dialog.exec();


    return ;

    auto upload = [=](QString sIp, QString sTarget, QString sPath)
    {
        //putty.exe -ssh -l pi -pw pi -P 22 192.168.0.157 -m mvModel0.txt
        QString sCmd =QApplication::applicationDirPath()+"/putty.exe -ssh -l pi -pw pi -P 22 "+sIp+" -m mvModel0.txt";

        system(sCmd.toStdString().c_str());

        CDATA.deleteDirectory(QApplication::applicationDirPath()+"/tmp/upload");

        if(!QDir(QApplication::applicationDirPath()+"/tmp").exists())
            QDir().mkdir(QApplication::applicationDirPath()+"/tmp");

        if(!QDir(QApplication::applicationDirPath()+"/tmp/upload").exists())
            QDir().mkdir(QApplication::applicationDirPath()+"/tmp/upload");

        if(!QDir(QApplication::applicationDirPath()+"/tmp/upload/model0").exists())
            QDir().mkdir(QApplication::applicationDirPath()+"/tmp/upload/model0");


        CDATA.copyDir(sTarget,QApplication::applicationDirPath()+"/tmp/upload/model0");

        //
        sCmd = QApplication::applicationDirPath()+"/pscp.exe -P 22 -pw \"pi\" -r %2 pi@%1:%3";

        sCmd = sCmd.arg(sIp).arg(QApplication::applicationDirPath()+"/tmp/upload/model0").arg(sPath);

        qDebug()<<"scmd : "<<sCmd;

        system(sCmd.toStdString().c_str());

    };

    //    upload(m_sPreIp," -r "+CDATA.m_sPath,"/home/pi/BoardT/bin/data/");

    //    return;

    DialogMsg msg;

    msg.setInput("請輸入IP",m_sPreIp,QStringList()<<"取消"<<"確定");

    int iRe = msg.exec();

    if(iRe==1)
    {
        m_sPreIp = msg.getInput();

        QString sPath = CDATA.m_sPath;

        //     QSettings conf(sPath+"/conf.ini",QSettings::IniFormat);


        QSettings conf(sPath+"/model0.BDM",QSettings::IniFormat);


        QDir dir(sPath);

        // conf.setValue("Target",dir.path().split("/").last());

        conf.setValue("DateTime",QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

        conf.sync();


        upload(m_sPreIp,sPath,"/home/pi/BoardT/bin/data/");

    }
}


void StageEditArea::on_btnToUsb_clicked()
{
    QString sTarget = QFileDialog::getExistingDirectory(
    this, "選擇USB根目錄",
    "/");
    // /BoardT/upload/model0

    if(!QDir(sTarget+"/BoardT").exists())
        QDir().mkdir(sTarget+"/BoardT");


    if(!QDir(sTarget+"/BoardT/upload").exists())
        QDir().mkdir(sTarget+"/BoardT/upload/");

    if(!QDir(sTarget+"/BoardT/upload/model0").exists())
        QDir().mkdir(sTarget+"/BoardT/upload/model0");

    CDATA.copyDir(CDATA.m_sPath,sTarget+"/BoardT/upload/model0");

}

