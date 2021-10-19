#include "LayerEditGrid.h"
#include "ui_LayerEditGrid.h"

LayerEditGrid::LayerEditGrid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerEditGrid)
{
    ui->setupUi(this);


    for(int i=0;i<9;i++)
    {
        TouchLabel *item = new TouchLabel(ui->wBg);

        item->hide();

        connect(item,&TouchLabel::clicked,this,&LayerEditGrid::slotClicked);

        m_listItem.append(item);
    }


}

LayerEditGrid::~LayerEditGrid()
{
    delete ui;
}

void LayerEditGrid::set4Grid(bool b)
{
    m_bIs4Grid = b;

}

void LayerEditGrid::showEvent(QShowEvent *)
{
    resetSize();
}

void LayerEditGrid::resizeEvent(QResizeEvent *)
{
    resetSize();
}

void LayerEditGrid::resetSize()
{
    int iColCount = 3;

    int iRowCount = 3;

    if(m_bIs4Grid)
    {
        iColCount = 2;

        iRowCount = 2;

    }
    int iW = ui->wBg->width()/iColCount;

    int iH = ui->wBg->height()/iRowCount;


    foreach(TouchLabel *item,m_listItem)
    {
        item->hide();
    }

    qDebug()<<"area : "<<iW<<" , "<<iH;
    int iIdx=0;

    for(int i=0;i<iRowCount;i++)
    {
        for(int j=0;j<iColCount;j++)
        {
            //  m_listItem[iIdx]->setGeometry(i*iH,j*iW,iW,iH);

            m_listItem[iIdx]->setMinimumSize(QSize(iW,iH));

            m_listItem[iIdx]->setMaximumSize(QSize(iW,iH));

            m_listItem[iIdx]->move(j*iW,i*iH);
            //item->setGeometry(i*iH,j*iW,iW,iH);
            m_listItem[iIdx]->show();

            iIdx++;
        }
    }



}

void LayerEditGrid::slotClicked()
{
    TouchLabel * item = dynamic_cast<TouchLabel*>(sender());

    foreach(TouchLabel *target,m_listItem)
    {
        item->setClicked(item == target);
    }
}

//=================================

TouchLabel::TouchLabel(QWidget *parent):QWidget(parent)
{
    m_lb = new QLabel(this);

    m_btn = new QPushButton(this);



//    QPushButton
//    {
//    color:rgb(14,14,14);
//    background-color: rgb(247,247,247);
//    border-style: outset;
//    border-radius: 10px;
//    padding:0px;
//    border-width: 2px;
//    border-color: #99b3d3;
//    font: 75 12px "Agency FB";
//    min-height:30px;
//    min-width:72px;
//    color:rgb(77,77,77);

//    }

//    QPushButton:hover
//    {
//    font: 75 14px "Agency FB";
//    border-color: gray;
//    border-width: 3px;

//    }

//    QPushButton:pressed
//    {
//    font: 75 16px "Agency FB";
//    border-color: black;
//    border-width: 3px;


    m_btn->setFlat(false);

    connect(m_btn,SIGNAL(clicked()),this,SLOT(slotClicked()));
}




void TouchLabel::setPic(QString sFile)
{
    QPixmap p(sFile);

    m_lb->setPixmap(p.scaledToHeight(height()));
}

void TouchLabel::setClicked(bool bIsClicked)
{
    m_bIsSelect = bIsClicked;


}

void TouchLabel::resetSize()
{
    qDebug()<<"one size "<<size();
    m_lb->setMinimumSize(size());

    m_lb->setMaximumSize(size());

    m_btn->setMinimumSize(size());

    m_btn->setMaximumSize(size());
}

void TouchLabel::showEvent(QShowEvent *)
{
    resetSize();
}

void TouchLabel::resizeEvent(QResizeEvent *)
{
    resetSize();
}

void TouchLabel::slotClicked()
{
    setClicked(true);

    emit clicked();
}
