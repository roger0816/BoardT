#include "LayerAddContent.h"
#include "ui_LayerAddContent.h"

LayerAddContent::LayerAddContent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerAddContent)
{
    ui->setupUi(this);

    m_listBtn<<ui->btnAddText<<ui->btnAddPic<<ui->btnAddVideo<<ui->btnAddBtn;


    foreach(QPushButton *btn,m_listBtn)
    {
        connect(btn,&QPushButton::clicked,this,&LayerAddContent::slotClicked);
    }

}

LayerAddContent::~LayerAddContent()
{
    delete ui;
}

void LayerAddContent::slotClicked()
{
    QPushButton *btn = dynamic_cast<QPushButton*>(sender());

    emit btnAddClicked(m_listBtn.indexOf(btn));
}
