#include "ItemTimeSchedule.h"
#include "ui_ItemTimeSchedule.h"

ItemTimeSchedule::ItemTimeSchedule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemTimeSchedule)
{
    ui->setupUi(this);
}

ItemTimeSchedule::~ItemTimeSchedule()
{
    delete ui;
}

void ItemWidgetClick::setFocus(bool b)
{

}
