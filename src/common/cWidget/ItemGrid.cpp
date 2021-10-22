#include "ItemGrid.h"
#include "ui_ItemGrid.h"

ItemGrid::ItemGrid(QWidget *parent) :
    ItemBaseObj(parent),
    ui(new Ui::ItemGrid)
{
    ui->setupUi(this);


    for(int i=0;i<9;i++)
    {
        QPushButton *btn = new QPushButton(ui->pageGrid);

        m_btns.addButton(btn,i);

        btn->hide();
    }

    connect(&m_btns,SIGNAL(buttonClicked(QAbstractButton *)),this,SLOT(slotClick(QAbstractButton *)));


//    m_btnMain = new QPushButton(ui->wBg);

//    m_btnMain->setText("回主選單");

//    m_btnMain->setMinimumSize(60,30);

//    m_btnMain->setMaximumSize(60,30);

//    m_btnMain->move(5,5);

//    m_btnMain->hide();

    m_btnBack = new QPushButton(ui->wBg);

    m_btnBack->setMinimumSize(100,30);

    m_btnBack->setMaximumSize(100,30);

    m_btnBack->move(5,5);

    m_btnBack->hide();

//    connect(m_btnMain,SIGNAL(clicked()),this,SLOT(slotBack()));


    connect(m_btnBack,SIGNAL(clicked()),this,SLOT(slotBack()));
}

ItemGrid::~ItemGrid()
{
    delete ui;
}

void ItemGrid::updateItem()
{
    if(m_obj==nullptr)
        return ;

    m_type = GRID_TYPE(m_obj->m_dataGrid.iCount);
    qDebug()<<"AAA : "<<m_obj->m_dataGrid.iCount;

    m_iCurrentLv = 1;

    m_iIdxLv1=0;

    m_iIdxLv2 = 0;

    reSetSize();



}

void ItemGrid::reSetSize()
{
    int iColCount = 3;

    int iRowCount = 3;

    if(m_type == GRID4)
    {
        iColCount = 2;

        iRowCount = 2;

    }
    int iW = ui->wBg->width()/iColCount;

    int iH = ui->wBg->height()/iRowCount;


    foreach(QAbstractButton *item,m_btns.buttons())
    {
        item->hide();
    }

    int iIdx=0;

    for(int i=0;i<iRowCount;i++)
    {
        for(int j=0;j<iColCount;j++)
        {
            //  m_listItem[iIdx]->setGeometry(i*iH,j*iW,iW,iH);

            QPushButton *btn = dynamic_cast<QPushButton*>(m_btns.buttons().at(iIdx));

            btn->setMinimumSize(QSize(iW,iH));

            btn->setMaximumSize(QSize(iW,iH));

            btn->move(j*iW,i*iH);
            //item->setGeometry(i*iH,j*iW,iW,iH);
            btn->show();

            iIdx++;
        }
    }

    refresh();
}

void ItemGrid::refresh()
{
    if(m_obj==nullptr)
        return ;


    m_btnBack->show();

    if(m_iCurrentLv ==3)
    {

        ui->stackedWidget->setCurrentWidget(ui->pageDetail);

        QPixmap p(m_obj->m_dataGrid.listG3[m_iIdxLv1].at(m_iIdxLv2));

        ui->label->setPixmap(p.scaledToHeight(ui->label->height()));


        m_btnBack->setText("返回");


    }

    else
    {
        ui->stackedWidget->setCurrentWidget(ui->pageGrid);


        for(int i=0;i<m_btns.buttons().length() && i<m_type;i++)
        {
            QStringList list = m_obj->m_dataGrid.listG1;
            if(m_iCurrentLv==2)
            {
                m_btnBack->setText("回主選單");

                list = m_obj->m_dataGrid.listG2[m_iIdxLv1];
            }
            else
            {
                m_btnBack->hide();
            }

            QPixmap p(list.at(i));

            QIcon btnIcon(p.scaledToHeight(m_btns.buttons()[i]->height()));

            m_btns.buttons()[i]->setIcon(btnIcon);

            QSize szPic = p.rect().size();
            m_btns.buttons()[i]->setIconSize(QSize(szPic.width(),szPic.height()));

        }

    }


}


void ItemGrid::slotClick(QAbstractButton *btn)
{
    int iId =  m_btns.id(btn);


    if(m_iCurrentLv==1)
    {
        m_iCurrentLv = 2;

        m_iIdxLv1 = iId;


    }
    else
    {
        m_iCurrentLv = 3;

        m_iIdxLv2 = iId;



    }

    refresh();
}

void ItemGrid::slotBack()
{
    if(m_iCurrentLv<=1)
        return;

    m_iCurrentLv--;

    refresh();
}


