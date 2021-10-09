#include "IconButton.h"
#include "ui_IconButton.h"

IconButton::IconButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IconButton)
{
    ui->setupUi(this);
    ui->wArea->setObjectName("wArea");

    ui->wArea->setStyleSheet("    QWidget#wArea \
    {    \
     background-color: white; \
        border-style: outset; \
        border-width: 2px; \
        border-radius: 10px; \
      border-color: #99b3d3; \
        font: bold 14px; \
    padding:0px; \
    }" );
}

IconButton::~IconButton()
{
    delete ui;
}

void IconButton::setData(QStringList listRes, QString sText)
{
    ui->lbText->setText(sText);

    if(listRes.length()<1)
        return;

    m_sResBase = listRes.first();
    while(listRes.length()<3)
    {
        listRes.append(m_sResBase);
    }

    m_sResFocus = listRes.at(1);

    m_sResClick = listRes.at(2);


    reSet(0);
}

void IconButton::setText(QString sText)
{
    ui->lbText->hide();

    ui->lbPic->setText(sText);
}

void IconButton::mouseMoveEvent(QMouseEvent *)
{

    qDebug()<<"mouse Move";
    reSet(1);

    //  ui->lbPic->setPixmap(QPixmap(m_sResFocus));
}

void IconButton::mousePressEvent(QMouseEvent *)
{

    ui->wArea->setStyleSheet("    QWidget#wArea \
    {    \
     background-color: black; \
        border-style: outset; \
        border-width: 8px; \
        border-radius: 10px; \
                border-color: black; \
        font: bold 14px; \
    padding:0px; \
    }" );

    reSet(2);
}

void IconButton::mouseReleaseEvent(QMouseEvent *)
{
    ui->wArea->setStyleSheet("    QWidget#wArea \
    {    \
     background-color: white; \
        border-style: outset; \
        border-width: 6px; \
        border-radius: 10px; \
                border-color: gray; \
        font: bold 14px; \
    padding:0px; \
    }" );
    reSet(0);
    emit clicked();
}

void IconButton::enterEvent(QEvent *event)
{

   ui->wArea->setStyleSheet("    QWidget#wArea \
   {    \
    background-color: white; \
       border-style: outset; \
       border-width: 6px; \
       border-radius: 10px; \
               border-color: gray; \
       font: bold 14px; \
   padding:0px; \
   }" );

}

void IconButton::leaveEvent(QEvent *event)
{
    ui->wArea->setStyleSheet("    QWidget#wArea \
    {    \
     background-color: white; \
        border-style: outset; \
        border-width: 2px; \
        border-radius: 10px; \
      border-color: #99b3d3; \
        font: bold 14px; \
    padding:0px; \
    }" );
}


void IconButton::showEvent(QShowEvent *event)
{
    reSet();
}

void IconButton::resizeEvent(QResizeEvent *event)
{
    ui->wArea->setMinimumWidth(ui->wArea->height());

     reSet();
}

void IconButton::reSet(int i)
{
    if(i!=m_iStatus || i<0)
    {

        QString sFilePath = m_sResBase;
        if(i==1)
        {
            sFilePath = m_sResFocus;
        }

        else if(i==2)
        {
            sFilePath = m_sResClick;
        }

        QPixmap p;



        ui->lbPic->setPixmap(QPixmap(sFilePath).scaledToHeight(ui->lbPic->height()-10));



        if(i>=0)
            m_iStatus = i;


    }
}
