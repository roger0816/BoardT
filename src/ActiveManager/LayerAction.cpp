#include "LayerAction.h"
#include "ui_LayerAction.h"

LayerAction::LayerAction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerAction)
{
    ui->setupUi(this);
}

LayerAction::~LayerAction()
{
    delete ui;
}
