#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);



    QString sDef = QApplication::applicationDirPath()+"/data/model0";

    CDATA;

    loadModel(sDef);

    connect(ui->wLayerSelector,&LayerSelector::sendSelectLayer,this,&Widget::slotSelector);

    connect(ui->wDisplay,&DisplayWidget::changeTarget,ui->wStyle,&LayerEditor::setTarget);

    connect(ui->wStyle,&LayerEditor::callUpdate,ui->wDisplay,&DisplayWidget::refreshItem);

    connect(ui->wStyle,&LayerEditor::callRaise,ui->wDisplay,&DisplayWidget::raiseItem);

    connect(ui->wStyle,&LayerEditor::callRename,ui->wDisplay,&DisplayWidget::renameItem);

    connect(ui->wStyle,&LayerEditor::callDelete,ui->wDisplay,&DisplayWidget::deleteItem);

    connect(ui->wAdd,&LayerAddContent::btnAddClicked,ui->wDisplay,&DisplayWidget::addItem);

    ui->wStackWork->setCurrentWidget(ui->page0);

    ui->wTop->hide();

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

        qDebug()<<"model no found : "<<sPath;
    }


    refreshSelector();


}



void Widget::on_btnSelectModel_clicked()
{
    QString sPath = QFileDialog::getOpenFileName(this,"選擇模組",QApplication::applicationDirPath()+"/data","*.BDM");

    QStringList listTmp = sPath.split("/");

    listTmp.pop_back();


    loadModel(listTmp.join("/"));

}

void Widget::on_btnAddModel_clicked()
{
    /**
    LayerNewModel dialog;

    dialog.setPath("新增模組",QApplication::applicationDirPath()+"/data/");

    int i =dialog.exec();

    if(i==1)
    {
        QString sTarget =dialog.m_sModelPath;

        QDir().mkdir(sTarget);

        QSettings conf(sTarget+"/"+sTarget.split("/").last()+".BDM",QSettings::IniFormat);

        conf.setValue("Base/default","Default");

        conf.sync();

        QString defLayer = sTarget+"/Default";

        QDir().mkdir(defLayer);

        QSettings def(defLayer+"/Default.BDT",QSettings::IniFormat);

        def.setValue("Base/resumeTimer",15);

        def.sync();

        loadModel(sTarget);
    }
    **/
}

void Widget::slotSelector(QString sName)
{

    ui->wStackWork->setCurrentWidget(ui->wWork);

    ui->wDisplay->setLayer(CDATA.m_sPath+"/"+sName);

    ui->wDisplay->setEdit(true);
}

void Widget::refreshSelector(bool bToDef)
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

void Widget::on_btnAddLayer_clicked()
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

void Widget::on_btnRemoveLayer_clicked()
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

void Widget::on_btnSave_clicked()
{
    DialogMsg msg;

    msg.setDialogInfo("確定要儲存嗎？",QStringList()<<"否"<<"是");

    int iRe = msg.exec();

    if(iRe == 1)
    {
        CDATA.writeModel();

        QString sPath = CDATA.m_sPath;

        QSettings conf(sPath+"/"+sPath.split("/").last()+".BDM",QSettings::IniFormat);

        QDir dir(sPath);

        // conf.setValue("Target",dir.path().split("/").last());

        conf.setValue("DateTime",QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

        conf.sync();


        refreshSelector();
    }
}



void Widget::on_btnUpload_clicked()
{
    DialogMsg msg;

    if(ui->lbModel->text().trimmed()=="")
    {
        msg.setDialogInfo("請先開啟模組",QStringList()<<"OK");

        msg.exec();

        return ;

    }




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


        upload(m_sPreIp," -r "+sPath,"/home/pi/BoardT/bin/data/");

    }
}

void Widget::upload(QString sIp, QString sTarget, QString sPath)
{
    // QString sCmd = QApplication::applicationDirPath()+"/pscp.exe -P 22 -pw \"pi\" -r "+m_sPath+" pi@"+m_sPreIp+":/home/pi/work/bin/";

    QString sCmd = QApplication::applicationDirPath()+"/pscp.exe -P 22 -pw \"pi\" %2 pi@%1:%3";

    sCmd = sCmd.arg(sIp).arg(sTarget).arg(sPath);

    qDebug()<<"scmd : "<<sCmd;

    system(sCmd.toStdString().c_str());


//    QProcess p;

//    p.start(sCmd.toStdString().c_str());

//    p.waitForFinished();
}



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

    QString sPath = QFileDialog::getOpenFileName(this,"選擇版面背景圖",QApplication::applicationDirPath(),"*.png");

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
