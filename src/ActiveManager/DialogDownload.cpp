#include "DialogDownload.h"
#include "ui_DialogDownload.h"

DialogDownload::DialogDownload(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDownload)
{
    ui->setupUi(this);

    setWindowTitle("下載");

    setTabOrder(ui->txtIp,ui->txtId);
}

DialogDownload::~DialogDownload()
{
    delete ui;
}

void DialogDownload::setIp(QString sIp)
{
    ui->txtIp->setText(sIp);
}

QString DialogDownload::ip()
{
    QString sRe = ui->txtIp->text();

    return sRe;
}

QString DialogDownload::id()
{
    QString sRe = ui->txtId->text();

    if(sRe.trimmed()=="")
        sRe = "pi";

    return sRe;
}

QString DialogDownload::pw()
{
    QString sRe = ui->txtPassword->text();

    if(sRe.trimmed()=="")
        sRe = "pi";

    return sRe;
}

void DialogDownload::on_btnCancel_clicked()
{
    reject();
}


void DialogDownload::on_btnOk_clicked()
{

    done(1);
}

