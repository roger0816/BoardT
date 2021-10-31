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



  //  QString sDef = QApplication::applicationDirPath()+"/data/model0";



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


    }
    else
    {

        CDATA.createModel(sPath);

        CDATA.readModel(sPath);

        qDebug()<<"model no found ,so create: "<<sPath;
    }


    ui->stackedWidget->setCurrentWidget(ui->stageEditArea);


}



void Widget::StageEditback()
{
    ui->stackedWidget->setCurrentWidget(ui->stageManager);
}










//void Widget::on_btnUploadUsb_clicked()
//{
//    DialogUploadUsb dialog;

//    dialog.resize(size()*0.6);

//    int re = dialog.exec();

//    if(re == 1)
//    {
//        QString sTarget = dialog.m_sPath;

//        // conf.setValue("Target",dir.path().split("/").last());

//        QString sPath = CDATA.m_sPath;

//        QSettings conf(sPath+"/"+sPath.split("/").last()+".BDM",QSettings::IniFormat);

//        QDir dir(sPath);


//        conf.setValue("DateTime",QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

//        conf.sync();

//        //   upload(m_sPreIp," -r "+sPath,"/home/pi/BoardT/bin/data/");

//        auto checkDir = [=](QString sDir)
//        {
//            if(!QDir(sDir).exists())
//            {
//                QDir().mkdir(sDir);
//            }
//        };


//        checkDir(sTarget+"/BoardT");

//        checkDir(sTarget+"/BoardT/bin");

//        checkDir(sTarget+"/BoardT/bin/data");

//        QString sCmd = "scp -r "+sPath+" "+sTarget+"/BoardT/bin/data";

//        system(sCmd.toStdString().c_str());

//    }
//}

