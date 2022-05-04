#include "DialogUploadNet.h"
#include "ui_DialogUploadNet.h"

DialogUploadNet::DialogUploadNet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUploadNet)
{
    ui->setupUi(this);

    setWindowTitle("網路上傳");

    while(m_listData.length()<10)
        m_listData.append(DataUploadNet());

    m_listData[0].ch = ui->ch_0;
    m_listData[0].txId = ui->txId_0;
    m_listData[0].txIp = ui->txIp_0;
    m_listData[0].txPass = ui->txPass_0;

    m_listData[1].ch = ui->ch_1;
    m_listData[1].txId = ui->txId_1;
    m_listData[1].txIp = ui->txIp_1;
    m_listData[1].txPass = ui->txPass_1;

    m_listData[2].ch = ui->ch_2;
    m_listData[2].txId = ui->txId_2;
    m_listData[2].txIp = ui->txIp_2;
    m_listData[2].txPass = ui->txPass_2;

    m_listData[3].ch = ui->ch_3;
    m_listData[3].txId = ui->txId_3;
    m_listData[3].txIp = ui->txIp_3;
    m_listData[3].txPass = ui->txPass_3;

    m_listData[4].ch = ui->ch_4;
    m_listData[4].txId = ui->txId_4;
    m_listData[4].txIp = ui->txIp_4;
    m_listData[4].txPass = ui->txPass_4;

    m_listData[5].ch = ui->ch_5;
    m_listData[5].txId = ui->txId_5;
    m_listData[5].txIp = ui->txIp_5;
    m_listData[5].txPass = ui->txPass_5;

    m_listData[6].ch = ui->ch_6;
    m_listData[6].txId = ui->txId_6;
    m_listData[6].txIp = ui->txIp_6;
    m_listData[6].txPass = ui->txPass_6;

    m_listData[7].ch = ui->ch_7;
    m_listData[7].txId = ui->txId_7;
    m_listData[7].txIp = ui->txIp_7;
    m_listData[7].txPass = ui->txPass_7;

    m_listData[8].ch = ui->ch_8;
    m_listData[8].txId = ui->txId_8;
    m_listData[8].txIp = ui->txIp_8;
    m_listData[8].txPass = ui->txPass_8;

    m_listData[9].ch = ui->ch_9;
    m_listData[9].txId = ui->txId_9;
    m_listData[9].txIp = ui->txIp_9;
    m_listData[9].txPass = ui->txPass_9;


    read();

}

DialogUploadNet::~DialogUploadNet()
{
    delete ui;
}

void DialogUploadNet::on_btnCancel_clicked()
{
    this->done(0);
}


void DialogUploadNet::on_btnOk_clicked()
{
    write();


    DialogMsg msg;

    msg.setDialogInfo("確定上傳嗎？",QStringList()<<"取消"<<"確定");

    int iRe = msg.exec();

    if(iRe==1)
    {


        QString sPath = CDATA.m_sPath;

        //     QSettings conf(sPath+"/conf.ini",QSettings::IniFormat);


        QSettings conf(sPath+"/model0.BDM",QSettings::IniFormat);


        QDir dir(sPath);

        // conf.setValue("Target",dir.path().split("/").last());

        conf.setValue("DateTime",QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

        conf.sync();

        for(int i=0;i<m_listData.length();i++)
        {
            DataUploadNet data = m_listData.at(i);

            if(data.ch->isChecked() && data.txIp->text().trimmed()!="")
            {
                upload(data.txIp->text(),data.txId->text(),data.txPass->text());

            }

        }


    }

    this->done(1);
}

void DialogUploadNet::read()
{
    QSettings conf(CDATA.m_sPath+"/model0.BDM",QSettings::IniFormat);

    for(int i=0;i<10;i++)
    {
           QStringList listData =  conf.value("Device/P"+QString::number(i)).toStringList();

           m_listData[i].setData(listData);
    }



}

void DialogUploadNet::write()
{
    QSettings conf(CDATA.m_sPath+"/model0.BDM",QSettings::IniFormat);

    for(int i=0;i<10;i++)
    {
           QStringList listData = m_listData[i].getData();

           conf.setValue("Device/P"+QString::number(i),listData);


    }

    conf.sync();


}

//void DialogUploadNet::upload(QString sIp, QString sTarget, QString sPath)
void DialogUploadNet::upload(QString sIp, QString sUser, QString sPassword)
{

    if(sUser.trimmed()=="")
        sUser="pi";

    if(sPassword.trimmed()=="")
        sPassword="pi";


    QString sPath = "/home/"+sUser+"/BoardT/bin/data/";

    QString sTarget = CDATA.m_sPath;


    //putty.exe -ssh -l pi -pw pi -P 22 192.168.0.157 -m mvModel0.txt
    QString sCmd =QApplication::applicationDirPath()+"/putty.exe -ssh -l %1 -pw %2 -P 22 "+sIp+" -m mvModel0.txt";

    system(sCmd.arg(sUser).arg(sPassword).toStdString().c_str());

    CDATA.deleteDirectory(QApplication::applicationDirPath()+"/tmp/upload");

    if(!QDir(QApplication::applicationDirPath()+"/tmp").exists())
        QDir().mkdir(QApplication::applicationDirPath()+"/tmp");

    if(!QDir(QApplication::applicationDirPath()+"/tmp/upload").exists())
        QDir().mkdir(QApplication::applicationDirPath()+"/tmp/upload");

    if(!QDir(QApplication::applicationDirPath()+"/tmp/upload/model0").exists())
        QDir().mkdir(QApplication::applicationDirPath()+"/tmp/upload/model0");


    CDATA.copyDir(sTarget,QApplication::applicationDirPath()+"/tmp/upload/model0");

    //
    sCmd = QApplication::applicationDirPath()+"/pscp.exe -P 22 -pw \"%5\" -r %2 %4@%1:%3";

    sCmd = sCmd.arg(sIp).arg(QApplication::applicationDirPath()+"/tmp/upload/model0").arg(sPath)
            .arg(sUser).arg(sPassword);

    qDebug()<<"scmd : "<<sCmd;

    system(sCmd.toStdString().c_str());
    
    sCmd =QApplication::applicationDirPath()+"/putty.exe -ssh -l %1 -pw %2 -P 22 "+sIp+" -m sync.txt";

    system(sCmd.arg(sUser).arg(sPassword).toStdString().c_str());

};


