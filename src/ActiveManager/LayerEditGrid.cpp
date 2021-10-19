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

//=================================

TouchLabel::TouchLabel(QWidget *parent):QWidget(parent)
{
    m_lb = new QLabel(this);

    m_btn = new QPushButton(this);

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
