#include "LayerEditGrid.h"
#include "ui_LayerEditGrid.h"

LayerEditGrid::LayerEditGrid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerEditGrid)
{
    ui->setupUi(this);


    for(int i=0;i<9;i++)
    {
        QPushButton *item = new QPushButton(ui->wBg);

        item->setCheckable(true);

        item->setStyleSheet("QPushButton:checked{"
                            "border-style:inset ; "
                            "border: 2px solid red;} ");


        item->hide();

        //  connect(item,&TouchLabel::clicked,this,&LayerEditGrid::slotClicked);

        m_listBtns.addButton(item,i);
    }

    m_listBtns.buttons().first()->setChecked(true);

    // connect(&m_listBtns,&QButtonGroup::buttonClicked,this,&LayerEditGrid::slotClicked);

}

LayerEditGrid::~LayerEditGrid()
{
    delete ui;
}

void LayerEditGrid::setObj(ObjData *obj)
{
    m_obj = obj;

    m_iGridCount = m_obj->m_dataGrid.iCount;
}



void LayerEditGrid::setListPic(QStringList list)
{
    for(int i=0;i<m_iGridCount && i<list.length();i++)
    {
        setPic(list.at(i),i);
    }

}

void LayerEditGrid::setPic(QString sFilePath, int iIdx)
{
    if(iIdx==-1)
        iIdx = m_listBtns.checkedId();

    QPixmap pixmap(sFilePath);
    QIcon btnIcon(pixmap.scaledToHeight(m_listBtns.buttons()[iIdx]->height()-2));

    m_listBtns.buttons()[iIdx]->setIcon(btnIcon);

    QSize szPic = pixmap.rect().size();
    m_listBtns.buttons()[iIdx]->setIconSize(QSize(szPic.width(),szPic.height()));


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

    if(m_iGridCount == 4)
    {
        iColCount = 2;

        iRowCount = 2;

    }
    int iW = ui->wBg->width()/iColCount;

    int iH = ui->wBg->height()/iRowCount;


    foreach(QAbstractButton *item,m_listBtns.buttons())
    {
        item->hide();
    }


    int iIdx=0;

    for(int i=0;i<iRowCount;i++)
    {
        for(int j=0;j<iColCount;j++)
        {
            //  m_listItem[iIdx]->setGeometry(i*iH,j*iW,iW,iH);

            QPushButton *btn = dynamic_cast<QPushButton*>(m_listBtns.buttons().at(iIdx));

            btn->setMinimumSize(QSize(iW,iH));

            btn->setMaximumSize(QSize(iW,iH));

            btn->move(j*iW,i*iH);
            //item->setGeometry(i*iH,j*iW,iW,iH);
            btn->show();

            iIdx++;
        }
    }



}



void LayerEditGrid::slotClicked(QAbstractButton *)
{
    emit clicked(m_listBtns.checkedId());
}

//=================================

//TouchLabel::TouchLabel(QWidget *parent):QWidget(parent)
//{
//    m_lb = new QLabel(this);

//    m_btn = new QPushButton(this);

//    m_btn->setCheckable(true);

//    m_btn->setStyleSheet(
//                        "QPushButton:checked{"
//                                     "border-style:inset ; "
//                                     "border: 2px solid red;} ");
//                      //  "QPushButton:pressed{background-color:red;}");
////    QPushButton
////    {
////    color:rgb(14,14,14);
////    background-color: rgb(247,247,247);
////    border-style: outset;
////    border-radius: 10px;
////    padding:0px;
////    border-width: 2px;
////    border-color: #99b3d3;
////    font: 75 12px "Agency FB";
////    min-height:30px;
////    min-width:72px;
////    color:rgb(77,77,77);

////    }

////    QPushButton:hover
////    {
////    font: 75 14px "Agency FB";
////    border-color: gray;
////    border-width: 3px;

////    }

////    QPushButton:pressed
////    {
////    font: 75 16px "Agency FB";
////    border-color: black;
////    border-width: 3px;


//    m_btn->setFlat(false);

//    connect(m_btn,SIGNAL(clicked()),this,SLOT(slotClicked()));
//}




//void TouchLabel::setPic(QString sFile)
//{
//    QPixmap p(sFile);

//    m_lb->setPixmap(p.scaledToHeight(height()));
//}

//void TouchLabel::setClicked(bool bIsClicked)
//{
//    m_bIsSelect = bIsClicked;


//}

//void TouchLabel::resetSize()
//{
//    qDebug()<<"one size "<<size();
//    m_lb->setMinimumSize(size());

//    m_lb->setMaximumSize(size());

//    m_btn->setMinimumSize(size());

//    m_btn->setMaximumSize(size());
//}

//void TouchLabel::showEvent(QShowEvent *)
//{
//    resetSize();
//}

//void TouchLabel::resizeEvent(QResizeEvent *)
//{
//    resetSize();
//}

//void TouchLabel::slotClicked()
//{
//    setClicked(true);

//    emit clicked();
//}
