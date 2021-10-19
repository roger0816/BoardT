#include "EditGrid.h"
#include "ui_EditGrid.h"

EditGrid::EditGrid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditGrid)
{
    ui->setupUi(this);
}

EditGrid::~EditGrid()
{
    delete ui;
}
