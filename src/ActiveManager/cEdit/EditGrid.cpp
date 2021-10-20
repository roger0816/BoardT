#include "EditGrid.h"
#include "ui_EditGrid.h"

EditGrid::EditGrid(QWidget *parent) :
    EditBase(parent),
    ui(new Ui::EditGrid)
{
    ui->setupUi(this);
}

EditGrid::~EditGrid()
{
    delete ui;
}


void EditGrid::setTarget(ObjData *obj)
{
    m_obj = obj;

    if(m_obj->m_dataGrid.iCount == 4)
    {
        ui->cbSelect->setCurrentIndex(0);
    }
    else
    {
        ui->cbSelect->setCurrentIndex(1);
    }

}

void EditGrid::on_btnSet_clicked()
{
    if(m_obj==nullptr)
        return;

    DialogEditGrid dialog;


    if(ui->cbSelect->currentIndex()==0)
        m_obj->m_dataGrid.iCount=4;
    else
        m_obj->m_dataGrid.iCount=9;

    dialog.setObj(m_obj);

    dialog.exec();
}

void EditGrid::on_cbSelect_currentIndexChanged(int index)
{
    if(m_obj==nullptr)
        return;

    if(index==0)
    {
        m_obj->m_dataGrid.iCount = 4;
    }
    else
    {
        m_obj->m_dataGrid.iCount = 9;
    }
}

