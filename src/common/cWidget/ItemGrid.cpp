#include "ItemGrid.h"
#include "ui_ItemGrid.h"

ItemGrid::ItemGrid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemGrid)
{
    ui->setupUi(this);
}

ItemGrid::~ItemGrid()
{
    delete ui;
}

void ItemGrid::setType(GRID_TYPE type)
{
    QGridLayout *lay = new QGridLayout;

    lay->setSpacing(0);

    lay->setMargin(0);

    if(type==GRID9)
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                QPushButton *btn = new QPushButton;

                btn->setFlat(true);

                QString sType = "background-color:rgb("+QString::number(i*110)+QString::number(j*110);

                btn->setStyleSheet(sType);

                lay->addWidget(btn,i,j);

                m_listButton.addButton(btn,i*j+j);
            }

        }



    }
}
