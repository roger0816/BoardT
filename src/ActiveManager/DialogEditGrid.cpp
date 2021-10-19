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

    ui->wG1->set4Grid(true);
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
