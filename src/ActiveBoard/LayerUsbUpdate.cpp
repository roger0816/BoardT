#include "LayerUsbUpdate.h"
#include "ui_LayerUsbUpdate.h"

LayerUsbUpdate::LayerUsbUpdate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerUsbUpdate)
{
    ui->setupUi(this);
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

void LayerUsbUpdate::detectUsb()
{
    ui->lbLast->setText("");

    ui->lbPath->setVisible(false);

    m_bCanDoit = false;


    if(m_listUsb.length()>0)
    {
        ui->lbLast->setVisible(true);

        ui->lbLast->setText(m_listUsb.last().split("/").last());


    }
}
