#include "LayerAddCompont.h"
#include "ui_LayerAddCompont.h"

LayerAddCompont::LayerAddCompont(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerAddCompont)
{
    ui->setupUi(this);
}

LayerAddCompont::~LayerAddCompont()
{
    delete ui;
}
