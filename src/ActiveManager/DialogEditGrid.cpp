#include "DialogEditGrid.h"
#include "ui_DialogEditGrid.h"

DialogEditGrid::DialogEditGrid(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditGrid)
{
    ui->setupUi(this);

    connect(ui->wG1,&LayerEditGrid::clicked,this,&DialogEditGrid::slotItemClicked);

    connect(ui->wG2,&LayerEditGrid::clicked,this,&DialogEditGrid::slotItemClicked);


}

DialogEditGrid::~DialogEditGrid()
{
    delete ui;
}

void DialogEditGrid::setObj(ObjData *obj)
{
    m_obj = obj;

    m_iCount = m_obj->m_dataGrid.iCount;

    ui->wG1->setObj(m_obj);

    ui->wG2->setObj(m_obj);
}


void DialogEditGrid::showEvent(QShowEvent *)
{
    resetSize();


}

void DialogEditGrid::resizeEvent(QResizeEvent *)
{
    resetSize();
}

void DialogEditGrid::resetSize()
{
//    ui->wG1->setGridCount(m_iCount);

//    ui->wG2->setGridCount(m_iCount);
    ui->wG1Area->setMinimumHeight((float)ui->wG1Area->width()/1080*720);
    ui->wG1Area->setMaximumHeight((float)ui->wG1Area->width()/1080*720);

    ui->wG2Area->setMinimumHeight((float)ui->wG2Area->width()/1080*720);
    ui->wG2Area->setMaximumHeight((float)ui->wG2Area->width()/1080*720);

    ui->wG3->setMinimumHeight((float)ui->wG3->width()/1080*720);
    ui->wG3->setMaximumHeight((float)ui->wG3->width()/1080*720);


}

void DialogEditGrid::on_btnG1SetListPic_clicked()
{
    QStringList listFile =QFileDialog::getOpenFileNames(this,QStringLiteral("選擇檔案"),
                                                        QApplication::applicationDirPath()+"/../",
                                                        "*.png *.jpg *jpeg");
    ui->wG1->setListPic(listFile);

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

void DialogEditGrid::slotItemClicked(int i)
{

}

void DialogEditGrid::slotG2ItemClicked(int i)
{

}
