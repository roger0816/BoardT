#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentWidget(ui->stageManager);

    connect(ui->stageManager,&StageManager::sendSelectModel,this,&Widget::loadModel);

    connect(ui->stageManager,&StageManager::sendUploadPage,this,&Widget::goUploadPage);


    connect(ui->stageEditArea,&StageEditArea::sendBack,this,&Widget::StageEditback);

    QTime t(QTime::fromString("01:02:03","hh:mm:ss"));

    QDateTime a= QDateTime::currentDateTime();

   qDebug()<<a;
    a = a.addMSecs(t.hour()*60*60*1000 + t.minute()*60*1000 + t.second()*1000);
    qDebug()<<a;

    qDebug()<<"cc : "<<t.hour()*60*60*1000 + t.minute()*60*1000 + t.second()*1000;
    qDebug()<<QDateTime::currentDateTime().msecsTo(a);

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

void Widget::goUploadPage(QString sPath)
{
    loadModel(sPath);

    ui->stageEditArea->on_btnUpload_clicked();

}



void Widget::StageEditback()
{
    ui->stackedWidget->setCurrentWidget(ui->stageManager);
}










