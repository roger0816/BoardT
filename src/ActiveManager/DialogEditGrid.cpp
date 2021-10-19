#include "DialogEditGrid.h"
#include "ui_DialogEditGrid.h"

DialogEditGrid::DialogEditGrid(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditGrid)
{
    ui->setupUi(this);



}

DialogEditGrid::~DialogEditGrid()
{
    delete ui;
}

void DialogEditGrid::showEvent(QShowEvent *)
{
    resetSize();

    ui->wG1->setGridCount(9);
}

void DialogEditGrid::resizeEvent(QResizeEvent *)
{
    resetSize();
}

void DialogEditGrid::resetSize()
{
    ui->wG1Area->setMinimumHeight((float)ui->wG1Area->width()/1080*720);
    ui->wG1Area->setMaximumHeight((float)ui->wG1Area->width()/1080*720);

    ui->wG2->setMinimumHeight((float)ui->wG2->width()/1080*720);
     ui->wG2->setMaximumHeight((float)ui->wG2->width()/1080*720);

    ui->wG3->setMinimumHeight((float)ui->wG3->width()/1080*720);
     ui->wG3->setMaximumHeight((float)ui->wG3->width()/1080*720);


}

void DialogEditGrid::on_btnG1SetListPic_clicked()
{
    QString sFile =QFileDialog::getOpenFileName(this,QStringLiteral("選擇檔案"),
                                                          QApplication::applicationDirPath()+"/../",
                                                          "*.png *.jpg *jpeg");

    ui->wG1->setPic(sFile);


}

void DialogEditGrid::on_btnG1SetPic_clicked()
{
    if(ui->wG1->currentId()<0)
    {
        DialogMsg msg;

        msg.setDialogInfo("請先選擇目標格",QStringList()<<"確認");

        msg.exec();
        return;
    }
    QString sFile =QFileDialog::getOpenFileName(this,QStringLiteral("選擇檔案"),
                                                          QApplication::applicationDirPath()+"/../",
                                                          "*.png *.jpg *jpeg");
    ui->wG1->setPic(sFile);
}
