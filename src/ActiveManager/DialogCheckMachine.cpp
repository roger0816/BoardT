#include "DialogCheckMachine.h"
#include "ui_DialogCheckMachine.h"

DialogCheckMachine::DialogCheckMachine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCheckMachine)
{
    ui->setupUi(this);

    startTimer(1000);

    m_listItem<<ui->w0<<ui->w1<<ui->w2<<ui->w3<<ui->w4<<ui->w5<<ui->w6<<ui->w7;

    while(m_listCheckIp.length()<m_listItem.length())
        m_listCheckIp.append("0");
}

DialogCheckMachine::~DialogCheckMachine()
{
    delete ui;
}

void DialogCheckMachine::timerEvent(QTimerEvent *)
{

    int iIdx = m_iSec%m_listItem.length();

    if(m_listCheckIp.indexOf(m_listItem[iIdx]->ip())<0 ||
            m_listCheckIp.indexOf(m_listItem[iIdx]->ip())==iIdx)
    {
        m_listCheckIp[iIdx] = m_listItem[iIdx]->ip();

        m_listItem[iIdx]->check();


    }
    m_iSec ++;

}

void DialogCheckMachine::showEvent(QShowEvent *)
{
    read();
}

void DialogCheckMachine::read()
{
    QSettings conf(CDATA.m_sPath+"/model0.BDM",QSettings::IniFormat);

    for(int i=0;i<m_listItem.length();i++)
    {
           QStringList listData =  conf.value("CheckMachine/P"+QString::number(i),QStringList()<<""<<"").toStringList();

           m_listItem[i]->setData(listData);
    }



}

void DialogCheckMachine::write()
{
    QSettings conf(CDATA.m_sPath+"/model0.BDM",QSettings::IniFormat);

    for(int i=0;i<m_listItem.length();i++)
    {
           QStringList listData = m_listItem.at(i)->getData();

           conf.setValue("CheckMachine/P"+QString::number(i),listData);


    }

    conf.sync();


}

void DialogCheckMachine::on_btnSave_clicked()
{
    DialogMsg msg;

    msg.setDialogInfo("確定要儲存IP嗎? " ,QStringList()<<"否"<<"是");

    if(msg.exec()==1)
    {
        write();
    }

}

