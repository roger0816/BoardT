#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_edit = new StageEdit();

    m_edit->hide();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnLayout_clicked()
{
    m_edit->show();
}
