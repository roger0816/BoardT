#include "ItemFunction.h"
#include "ui_ItemFunction.h"

ItemFunction::ItemFunction(QWidget *parent) :
    ItemBase(parent),
    ui(new Ui::ItemFunction)
{
    ui->setupUi(this);



   // ui->btnMsg->setEnabled(false);

    connect(&Global::Instance().m_nfc,&FuncNfc::hoverUid
            ,this,&ItemFunction::nfc);


    startTimer(1000);

}

ItemFunction::~ItemFunction()
{
    delete ui;
}




void ItemFunction::on_btnPause_clicked()
{
    Global::Instance().setTouch();

    Global::Instance().setAllStop(!Global::Instance().allStop());

    if(Global::Instance().allStop())
    {

        ui->btnPause->setText("RESUME");

        qDebug()<<"send : "<<false;

        emit sendPlay(false);
    }
    else
    {
        ui->btnPause->setText("PAUSE");

        emit sendPlay(true);

        qDebug()<<"send : "<<true;
    }
}

void ItemFunction::on_btnQrcode_clicked()
{
    Global::Instance().setTouch();

    Global::Instance().m_dialogPop->setQrCode(config("Qr/code").toString(),QRect(100,900,400,400));

}

//void ItemFunction::on_btnOther_clicked()
//{
//    emit sendRefresh();
//}

void ItemFunction::on_btnMsg_clicked()
{

    msg.setFocus();

    msg.exec();
}

void ItemFunction::timerEvent(QTimerEvent *)
{

    m_iTimeSec--;

    if(m_iTimeSec<0)
        m_iTimeSec=0;


    if(m_iTimeSec==1)
    {
        if(Global::Instance().m_nfc.getUid().trimmed()!="")
        {
            m_iTimeSec = 8;
             ui->btnMsg->setEnabled(true);
        }
        else {
          //  ui->btnMsg->setEnabled(false);
        }
    }


}

void ItemFunction::nfc(QString sId)
{

    ui->btnMsg->setEnabled(true);

    m_iTimeSec = 8;

    QString sFile ="/home/pi/work/bin/outData/%1_%2";

    msg.m_sSavePath = sFile.arg(sId).arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));;

}
