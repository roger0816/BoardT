#include "LayerUsbUpdate.h"
#include "ui_LayerUsbUpdate.h"

static QString msg_finish= "更新完成";

static QString msg_updating="更新中...";

LayerUsbUpdate::LayerUsbUpdate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerUsbUpdate)
{
    ui->setupUi(this);

    ui->process->setRange(0,100);

    startTimer(100);
}

LayerUsbUpdate::~LayerUsbUpdate()
{
    delete ui;
}

void LayerUsbUpdate::showEvent(QShowEvent *)
{

    detectUsb();

}

void LayerUsbUpdate::setUsbList(QStringList listUsb)
{
    m_listUsb = listUsb;

    detectUsb();
}

void LayerUsbUpdate::doUpdate()
{
    m_bLock = true;

    ui->lbMsg->setText(msg_updating);

    QString sCmd = "rm -rf ~/BoardT/bin/data/model0BK";

    system(sCmd.toStdString().c_str());

    sCmd = "mv ~/BoardT/bin/data/model0 ~/BoardT/bin/data/model0BK";

    system(sCmd.toStdString().c_str());

    sCmd = "cp -r "+m_listUsb.last()+"/BoardT/upload/model0 ~/BoardT/bin/data/";

    qDebug()<<sCmd;
    system(sCmd.toStdString().c_str());


    ui->lbMsg->setText(msg_finish);
}

void LayerUsbUpdate::callHide()
{
    if(m_bWaitHide)
        return ;

    m_bWaitHide = true;


    doHide();


}

void LayerUsbUpdate::detectUsb()
{
    ui->lbLast->setText("");

    ui->lbMsg->setText("");

    ui->lbPath->setVisible(false);

    m_bCanDoit = false;

    m_bLock = false;

    ui->process->setValue(0);


    if(m_listUsb.length()>0)
    {
        ui->lbLast->setVisible(true);

        ui->lbLast->setText(m_listUsb.last().split("/").last());

        m_bCanDoit = checkPath(m_listUsb.last());

    }
}

bool LayerUsbUpdate::checkPath(QString sPath)
{
    bool bHasPath = false;

    QDir sDir(sPath+"/BoardT/upload/model0");

    bHasPath = sDir.exists();

    ui->lbPath->setVisible(bHasPath);

    return bHasPath;
}

void LayerUsbUpdate::timerEvent(QTimerEvent *)
{
    if(m_bCanDoit && isVisible())
    {
        if(ui->process->value()<100)
        {
            ui->process->setValue(ui->process->value()+5);


        }
        else
        {
            if(!m_bLock)
            {

                doUpdate();
            }

        }


    }
}

void LayerUsbUpdate::doHide()
{
    if(ui->lbMsg->text()==msg_updating)
    {
        QTimer::singleShot(1000,this,SLOT(doHide()));
    }
    else if(ui->lbMsg->text()==msg_finish)
    {
         m_bWaitHide = false;
         QTimer::singleShot(2000,this,SLOT(hide()));
    }
    else
    {
        m_bWaitHide = false;
        QTimer::singleShot(300,this,SLOT(hide()));
    }

}
