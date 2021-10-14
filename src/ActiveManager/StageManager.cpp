#include "StageManager.h"
#include "ui_StageManager.h"

StageManager::StageManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageManager)
{
    ui->setupUi(this);

    ui->btnUpload->setData(QStringList()<<":/button/folder-html-icon.png","上傳專案");

    ui->btnDownload->setData(QStringList()<<":/button/folder-downloads-icon.png","下載專案");
    connect(ui->btnUpload,&IconButton::clicked,this,&StageManager::slotBtnUpload);

    connect(&m_listBtn,&QButtonGroup::idClicked,this,&StageManager::slotRadioClicked);

    m_lay = new QGridLayout;

    addData(QDir(QApplication::applicationDirPath()+"/data").entryList(QDir::Dirs | QDir::NoDotAndDotDot),false);

    if(m_listBtn.buttons().length()>0)
    {
        m_listBtn.buttons()[0]->setChecked(true);

        slotRadioClicked(0);

    }


}

StageManager::~StageManager()
{
    delete ui;
}

void StageManager::on_btnNewModel_clicked()
{

    DialogMsg msg;

    msg.setInput("新增專案\n\n請設定名稱","",QStringList()<<"取消"<<"確定");

    if(msg.exec()==0)
        return;

    QString sName = msg.getInput();
    //qDeleteAll(ui->wSpace->children());

    addData(QStringList()<<sName);



}

void StageManager::addData(QStringList list, bool bNew)
{
    for(int i=0;i<list.length();i++)
    {

        QCheckBox * t = new QCheckBox();

        QFont font;

        font.setPixelSize(22);

        font.setBold(true);

        t->setFont(font);

        t->setMinimumSize(QSize(120,30));

        t->setMaximumSize(QSize(120,30));

        m_listBtn.addButton(t,m_listBtn.buttons().length());



        m_listKey.append(list.at(i));

        if(bNew)
            CDATA.createModel(list.at(i));
    }

    delete  m_lay;

    m_lay = new QGridLayout;

    m_lay->setMargin(40);

    for(int i=0;i<m_listBtn.buttons().length();i++)
    {
        m_lay->addWidget(m_listBtn.buttons()[i],i/5,i%5);

        m_listBtn.buttons()[i]->setText(m_listKey.at(i));
    }

    ui->wSpace->setLayout(m_lay);



}

void StageManager::on_btnDelete_clicked()
{

    if(m_listBtn.checkedId()<0)
    {
        DialogMsg msg;

        msg.setDialogInfo("請先選擇目標",QStringList()<<"OK");

        msg.exec();


        return ;
    }


    DialogMsg msg2;

    msg2.setDialogInfo("確定要刪除 '"+m_listKey.at(m_listBtn.checkedId())+"' 嗎?",QStringList()<<"取消"<<"確認");

    if(msg2.exec()==0)
        return;


    m_listKey.removeAt(m_listBtn.checkedId());

    m_listBtn.removeButton(m_listBtn.button(m_listBtn.checkedId()));


    delete  m_lay;

    m_lay = new QGridLayout;


    for(int i=0;i<m_listBtn.buttons().length();i++)
    {
        m_lay->addWidget(m_listBtn.buttons()[i],i/5,i%5);

        m_listBtn.buttons()[i]->setText(m_listKey.at(i));
    }

    ui->wSpace->setLayout(m_lay);



}

void StageManager::on_btnEdit_clicked()
{
    if(m_listBtn.checkedId()<0)
    {
        DialogMsg msg;

        msg.setDialogInfo("請先選擇目標",QStringList()<<"OK");

        msg.exec();


        return ;
    }

    QString sPath = QApplication::applicationDirPath()+"/data/"+m_listKey.at(m_listBtn.checkedId());

    emit sendSelectModel(sPath);

    // loadModel(QApplication::applicationDirPath()+"/data/"+m_listKey.at(m_listBtn.checkedId()));


}

void StageManager::slotBtnUpload()
{
    auto upload = [=](QString sIp, QString sTarget, QString sPath)
    {
        //putty.exe -ssh -l pi -pw pi -P 22 192.168.0.157 -m mvModel0.txt
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


            upload(m_sPreIp," -r "+sPath,"/home/pi/BoardT/bin/data/");

        }
}

void StageManager::slotRadioClicked(int)
{
    QString sPath = QApplication::applicationDirPath()+"/data/"+m_listKey.at(m_listBtn.checkedId());

    qDebug()<<"AAA "<<sPath;
    CDATA.readModel(sPath);

}
