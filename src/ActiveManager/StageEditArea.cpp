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
    emit sendBack();
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

        QSettings conf(sPath+"/"+sPath.split("/").last()+".BDM",QSettings::IniFormat);

        QDir dir(sPath);

        // conf.setValue("Target",dir.path().split("/").last());

        conf.setValue("DateTime",QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

        conf.sync();


        refreshSelector();
    }
}

void StageEditArea::on_btnUpload_clicked()
{

    auto fnSave =[=]()
    {
        int iScheduleStatus = SCHEDULE_OFF;

        CDATA.m_dataModel.iScheduleMode = iScheduleStatus;


        CDATA.writeModel(ui->wLayerSelector->m_sSetTargetPath);

        QString sPath = CDATA.m_sPath;

        QSettings conf(sPath+"/"+sPath.split("/").last()+".BDM",QSettings::IniFormat);

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


        QSettings conf(sPath+"/"+sPath.split("/").last()+".BDM",QSettings::IniFormat);


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

    QString sPath = QFileDialog::getOpenFileName(this,"選擇版面背景圖",QApplication::applicationDirPath(),"*.png *jpg *jpeg");

    if(sPath != CDATA.m_dData[sTarget]->m_sBgPath)
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
