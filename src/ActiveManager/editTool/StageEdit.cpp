#include "StageEdit.h"
#include "ui_StageEdit.h"

StageEdit::StageEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageEdit)
{
    ui->setupUi(this);

    checkDir();

    m_wTarget = ui->wCent;

    connect(m_wTarget,SIGNAL(sendItemUpdate()),this,SLOT(slotItemUpdate()));

    ui->stackType->setCurrentWidget(ui->pgNone);


    m_wTarget->setTypeMapping(QApplication::applicationDirPath()+"/data/layer/define.ini");

    connect(ui->pgText,SIGNAL(updateData()),this,SLOT(slotEditChange()));


    ui->stackWidget0->setCurrentWidget(ui->pageNone);
}

StageEdit::~StageEdit()
{
    delete ui;
}

void StageEdit::editType(int i)
{

    ui->txtName->setText(m_wTarget->m_currentItem->m_sName);

    if(i==m_dDefine.value(E_TEXT))
    {
        ui->stackType->setCurrentWidget(ui->pgText);

    }
}

void StageEdit::on_btnLabel_clicked()
{

    ui->stackType->setCurrentWidget(ui->pgText);


    ui->txtName->setText(m_wTarget->setNewContent(E_TEXT));


}




void StageEdit::on_btnToTop_clicked()
{
//    foreach(ItemContent *item ,m_listItem)
//    {
//        if(item->getRoll())
//        {
//            item->raise();
//        }
//    }
}



void StageEdit::on_btnCreate_clicked()
{
    LayerNewModel dialog;

    int i =dialog.exec();

    if(i==1)
    {

        m_wTarget->clearUi();

        m_sPath = dialog.m_sModelPath;

        ui->lbTitle->setText(m_sPath.split("/").last());

        ui->stackWidget0->setCurrentWidget(ui->page0);
    }
}

void StageEdit::on_btnSave_clicked()
{
   DialogMsg msg;

   msg.setDialogInfo("確定要儲存嗎？",QStringList()<<"否"<<"是");

   int iRe = msg.exec();

   if(iRe == 1)
    m_wTarget->saveFile(m_sPath);
}

void StageEdit::on_btnOpen_clicked()
{
    //    QString dir = QFileDialog::getExistingDirectory(
    //                this, tr("選擇樣版"),
    //                QApplication::applicationDirPath()+"/data/layer/",
    //                QFileDialog::ShowDirsOnly
    //                | QFileDialog::DontResolveSymlinks);



    QString sTmp = QFileDialog::getOpenFileName(this, tr("選擇樣版"),
                                                QApplication::applicationDirPath()+"/data/layer/","*.BDT");
    QFileInfo ff(sTmp);



    QString dir = ff.path();

        if(dir =="")
            return;

        m_sPath = dir;

        m_wTarget->loadFile(m_sPath);

        slotItemUpdate();

        ui->lbTitle->setText(m_sPath.split("/").last());

        ui->stackWidget0->setCurrentWidget(ui->page0);
}



void StageEdit::slotItemUpdate()
{

    ItemContent *current = m_wTarget->m_currentItem;

    ui->txtName->setText(m_wTarget->m_currentItem->m_sName);

    ui->sbX->setValue(current->pos().x()/m_wTarget->m_fDiffSize);

    ui->sbY->setValue(current->pos().y()/m_wTarget->m_fDiffSize);

    ui->sbW->setValue(current->width()/m_wTarget->m_fDiffSize);

    ui->sbH->setValue(current->height()/m_wTarget->m_fDiffSize);


    if(m_wTarget->currentItemType() == E_TEXT)
    {
        ui->stackType->setCurrentWidget(ui->pgText);

        ui->pgText->setData(current->m_dataText);


    }
}

void StageEdit::slotEditChange()
{

    if(sender() == ui->pgText)
    {
        m_wTarget->setTxData(ui->pgText->getData());

    }
}



void StageEdit::on_btnRename_clicked()
{

      m_wTarget->rename(ui->txtName->text().trimmed());

}


void StageEdit::on_btnTest_clicked()
{
    QString sApp = QApplication::applicationDirPath()+"/ActiveBoard.exe %1";

    sApp = sApp.arg(QApplication::applicationDirPath()+"/data/layer/"+ui->lbTitle->text());

    QProcess p;

    p.setWorkingDirectory(QApplication::applicationDirPath());

    p.startDetached(sApp);

    // system(sApp.toStdString().c_str());
}

void StageEdit::checkDir()
{

    QStringList list;

    list<<QApplication::applicationDirPath()+"/data";

    list<<QApplication::applicationDirPath()+"/data/layer";

    list<<QApplication::applicationDirPath()+"/data/video";


    foreach(QString st,list)
    {
        if(!QDir(st).exists())
        {
            QDir().mkdir(st);
        }
    }


    QFileInfo fileDefine(QApplication::applicationDirPath()+"/data/layer/define.ini");

    if(!fileDefine.exists())
    {
        QSettings setting(QApplication::applicationDirPath()+"/data/layer/define.ini",QSettings::IniFormat);

        setting.setValue("text",1);

        setting.setValue("pic",2);

        setting.setValue("button",3);

        setting.setValue("dateTime",4);

        setting.setValue("web",5);

        setting.setValue("function",6);

        setting.setValue("video",7);


        setting.setValue("logo",8);

        setting.setValue("ticket",9);

        setting.setValue("active",10);

        setting.setValue("onSale",14);


        setting.setValue("mediaCent",17);

        setting.sync();



    }




}

void StageEdit::on_btnMainBg_clicked()
{
    QString sPath = QFileDialog::getOpenFileName(this,"選擇元件背景圖",QApplication::applicationDirPath(),"*.png");

    m_wTarget->setBgImage(sPath);

}

void StageEdit::on_sbX_valueChanged(int arg1)
{
    m_wTarget->m_currentItem->move(arg1*m_wTarget->m_fDiffSize,m_wTarget->m_currentItem->y());

}

void StageEdit::on_sbY_valueChanged(int arg1)
{
    m_wTarget->m_currentItem->move(m_wTarget->m_currentItem->x(),arg1*m_wTarget->m_fDiffSize);
}

void StageEdit::on_sbW_valueChanged(int arg1)
{
    m_wTarget->m_currentItem->resize(arg1*m_wTarget->m_fDiffSize,m_wTarget->m_currentItem->height());

}

void StageEdit::on_sbH_valueChanged(int arg1)
{
        m_wTarget->m_currentItem->resize(m_wTarget->m_currentItem->width(),arg1*m_wTarget->m_fDiffSize);
}


void StageEdit::on_btnUpload_clicked()
{

       DialogMsg msg;

    if(ui->lbTitle->text().trimmed()=="")
    {
        msg.setDialogInfo("請先開啟樣版",QStringList()<<"OK");

        msg.exec();

        return ;

    }


    msg.setInput("請輸入IP",m_sPreIp,QStringList()<<"取消"<<"確定");

    int iRe = msg.exec();

    if(iRe==1)
    {
        m_sPreIp = msg.getInput();


        QSettings conf(m_sPath+"/../conf.ini",QSettings::IniFormat);

        QDir dir(m_sPath);

        conf.setValue("Target",dir.path().split("/").last());

        conf.setValue("DateTime",QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

        conf.sync();

        upload(m_sPreIp,m_sPath+"/../conf.ini","/home/pi/work/bin/data/layer");

        upload(m_sPreIp,m_sPath+"/../define.ini","/home/pi/work/bin/data/layer");


        upload(m_sPreIp," -r "+m_sPath,"/home/pi/work/bin/data/layer");

    }

}

void StageEdit::upload(QString sIp, QString sTarget, QString sPath)
{
   // QString sCmd = QApplication::applicationDirPath()+"/pscp.exe -P 22 -pw \"pi\" -r "+m_sPath+" pi@"+m_sPreIp+":/home/pi/work/bin/";

    QString sCmd = QApplication::applicationDirPath()+"/pscp.exe -P 22 -pw \"pi\" %2 pi@%1:%3";

    sCmd = sCmd.arg(sIp).arg(sTarget).arg(sPath);

    qDebug()<<"scmd : "<<sCmd;

    system(sCmd.toStdString().c_str());

}
