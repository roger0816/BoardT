#include "DialogPicDetail.h"
#include "ui_DialogPicDetail.h"

DialogPicDetail::DialogPicDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPicDetail)
{
    ui->setupUi(this);

    setWindowFlag(Qt::WindowMaximizeButtonHint);
}

DialogPicDetail::~DialogPicDetail()
{
    delete ui;
}

void DialogPicDetail::setPicPath(QString sPathFile)
{
    m_sFilePath = sPathFile;

    ui->label->setPixmap(QPixmap(m_sFilePath).scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio));
}

void DialogPicDetail::resizeEvent(QResizeEvent *)
{
    ui->label->setPixmap(QPixmap(m_sFilePath).scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio));
}

void DialogPicDetail::showEvent(QShowEvent *)
{
     ui->label->setPixmap(QPixmap(m_sFilePath).scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio));
}
