#include "DialogUploadUsb.h"
#include "ui_DialogUploadUsb.h"

DialogUploadUsb::DialogUploadUsb(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUploadUsb)
{
    ui->setupUi(this);
}

DialogUploadUsb::~DialogUploadUsb()
{
    delete ui;
}

void DialogUploadUsb::on_btnSelect_clicked()
{

    m_sPath = QFileDialog::getExistingDirectory(this, tr("選擇USB根目錄"),
                                                "/",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);




}

