#include "ItemCheckMachine.h"
#include "ui_ItemCheckMachine.h"

ItemCheckMachine::ItemCheckMachine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemCheckMachine)
{
    ui->setupUi(this);

    mkdir();


    m_cmd = new QProcess(this);

    connect(m_cmd,SIGNAL(finished(int)),this,SLOT(slotFinish(int)));

    connect(ui->lbPic,&LabelCheckMachine::clicked,this,&ItemCheckMachine::slotClicked);
    //    startTimer(1000);

    ui->btnChangeName->setEnabled(false);

    ui->btnReboot->setEnabled(false);

}

ItemCheckMachine::~ItemCheckMachine()
{
    delete ui;
}

QString ItemCheckMachine::ip()
{
    return ui->txIp->text().trimmed();
}

void ItemCheckMachine::setData(QStringList listData)
{

    m_sIp = listData.first();

    ui->txIp->setText(m_sIp);

    m_sUser = listData.last();

    ui->txUser->setText(m_sUser);


}

QStringList ItemCheckMachine::getData()
{
    return QStringList()<<m_sIp<<m_sUser;
}

void ItemCheckMachine::check()
{

    if(ui->txIp->text().trimmed()!="" && m_cmd->state() != QProcess::Running)
    {

        m_sIp = ui->txIp->text().trimmed();

        m_sUser = ui->txUser->text().trimmed();

        if(m_sUser.trimmed()=="")
            m_sUser = "pi";

        m_sPassword = ui->txPass->text().trimmed();

        if(m_sPassword.trimmed()=="")
            m_sPassword = "pi";

        m_cmd->start("ping "+m_sIp+" -n 1 -i 2");

    }
    else
    {
        m_sIp="";
    }
}


bool ItemCheckMachine::deleteDirectory(const QString &path)
{

    if (path.isEmpty())
        return false;

    QDir dir(path);
    if(!dir.exists())
        return true;

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList)
    {
        if (fi.isFile())
            fi.dir().remove(fi.fileName());
        else
            deleteDirectory(fi.absoluteFilePath());
    }
    return dir.rmpath(dir.absolutePath());


}

QString ItemCheckMachine::mkdir(QString sPath)
{
    QString st = QApplication::applicationDirPath()+"/screen/"+sPath;

    if(!QDir(st).exists())
        QDir().mkdir(st);

    return st;
}

QString ItemCheckMachine::getDeviceInfo()
{


    QString sRe="";

    QString sPath = mkdir(ui->txIp->text().trimmed());

    QFile(sPath+"/deviceInfo").remove();

    QString sCmd = QApplication::applicationDirPath()+"/pscp.exe -P 22 -pw \"%1\" %2@%3:%4 %5";

    sCmd = sCmd.arg(m_sPassword).arg(m_sUser).arg(m_sIp).arg("deviceInfo").arg(sPath);

    cmd(sCmd);

    bool bOk = false;

    QFile file(sPath+"/deviceInfo");
    if(file.exists() && file.open(QIODevice::ReadOnly))
    {

        sRe = file.readLine();

        ui->lbDeviceName->setText(sRe.trimmed());

        file.close();



        bOk = true;

    }


    connectOk(bOk);





    return sRe;
}

void ItemCheckMachine::setDeviceInfo()
{
    QString sPath = mkdir(ui->txIp->text().trimmed());


    QFile file(sPath+"/deviceInfo");

    if(file.open(QIODevice::WriteOnly))
    {

        QTextStream out(&file);

        out<<ui->txDeviceName->text().trimmed()<<"\n";

        file.close();
    }

    QString sCmd = QApplication::applicationDirPath()+"/pscp.exe -P 22 -pw \"%1\"  %5 %2@%3:%4";

    sCmd = sCmd.arg(m_sPassword).arg(m_sUser).arg(m_sIp).arg("").arg(sPath+"/deviceInfo");

    cmd(sCmd);

    getDeviceInfo();

}

void ItemCheckMachine::getScreen()
{


    //putty.exe -ssh -l pi -pw pi -P 22 192.168.0.157 -m scrot.txt

    QString sCmd =QApplication::applicationDirPath()+"/plink.exe -ssh -l \"%1\" -pw \"%2\" -P 22 "+m_sIp+" -m scrot.txt";
    //C:/work/q_project/BoardT/bin/plink.exe -ssh -l pi -pw pi -P 22 192.168.1.108 -m scrot.txt
    sCmd = sCmd.arg(m_sUser).arg(m_sPassword);

    cmd(sCmd);  //QProcess


    QString sPath = mkdir(ui->txIp->text().trimmed());

    sCmd = QApplication::applicationDirPath()+"/pscp.exe -P 22 -pw \"%1\" %2@%3:%4 %5";

    sCmd = sCmd.arg(m_sPassword).arg(m_sUser).arg(m_sIp).arg("screen.png").arg(sPath);

    cmd(sCmd);

    m_sPicPath =sPath+"/screen.png";

    ui->lbPic->setPixmap(QPixmap(m_sPicPath).scaled(ui->lbPic->width(),ui->lbPic->height(),Qt::KeepAspectRatio));

    m_bPicOk = true;

}

void ItemCheckMachine::pingOk(bool bOk)
{
    if(bOk)
    {
        ui->lbIpStatus->setStyleSheet("background-color: rgb(0, 255, 0);"
                                      "color: rgb(255, 255, 255); \
                                      border: 2px  solid gray;  \
                border-radius: 5px;");




        getDeviceInfo();

        getScreen();
    }
    else
    {
        ui->lbIpStatus->setStyleSheet("background-color: rgb(255, 0, 0);"
                                      "color: rgb(255, 255, 255); \
                                      border: 2px  solid gray; \
                border-radius: 5px;");

        ui->lbPassStatus->setStyleSheet("background-color: rgb(255, 0, 0);"
                                        "color: rgb(255, 255, 255); \
                                        border: 2px  solid gray; \
                border-radius: 5px;");

        ui->lbDeviceName->clear();

        ui->lbPic->setPixmap(QPixmap());

        m_bPicOk = false;
    }


}

void ItemCheckMachine::connectOk(bool bOk)
{

    if(bOk)
    {
        ui->lbPassStatus->setStyleSheet("background-color: rgb(0, 255, 0);"
                                        "color: rgb(255, 255, 255); \
                                        border: 2px  solid gray; \
                border-radius: 5px;");
    }
    else
    {
        ui->lbDeviceName->clear();

        ui->lbPassStatus->setStyleSheet("background-color: rgb(255, 0, 0);"
                                        "color: rgb(255, 255, 255); \
                                        border: 2px  solid gray; \
                border-radius: 5px;");
    }

    ui->btnChangeName->setEnabled(bOk);

    ui->btnReboot->setEnabled(bOk);


}

void ItemCheckMachine::cmd(QString st)
{
    QProcess p;

    p.start(st);

    QEventLoop loop;

    connect(&p,SIGNAL(finished(int)),&loop,SLOT(quit()));

    loop.exec();
}



void ItemCheckMachine::slotFinish(int)
{
    QByteArray out = m_cmd->readAllStandardOutput();

    if(!out.isEmpty())
    {
        QString st = QString::fromLocal8Bit(out);

        //  ui->label->setText(st);

        QStringList listSt = st.split("\r\n");

        if(listSt.first().trimmed()=="" && listSt.length()>1)
            listSt.pop_front();

        if(listSt.last().trimmed()=="" && listSt.length()>1)
            listSt.pop_back();

        bool bOk = st.contains("TTL=");

        pingOk(bOk);




    }
}

void ItemCheckMachine::slotClicked()
{
    if(!m_bPicOk)
        return;

    DialogPicDetail dialog;

    dialog.setPicPath(m_sPicPath);

    dialog.setWindowTitle("");

    dialog.exec();
}



void ItemCheckMachine::on_btnChangeName_clicked()
{
    DialogMsg msg;

    msg.setDialogInfo("確定要變更設備名稱嗎? " ,QStringList()<<"否"<<"是");

    if(msg.exec()==1)
    {
        setDeviceInfo();
    }
}



void ItemCheckMachine::on_btnReboot_clicked()
{
    DialogMsg msg;

    msg.setDialogInfo("確定要此設備重開機嗎? " ,QStringList()<<"否"<<"是");

    if(msg.exec()==1)
    {
        QString sCmd =QApplication::applicationDirPath()+"/plink.exe -ssh -l \"%1\" -pw \"%2\" -P 22 "+m_sIp+" -m reboot.txt";

        sCmd = sCmd.arg(m_sUser).arg(m_sPassword);

        cmd(sCmd);

    }
}

