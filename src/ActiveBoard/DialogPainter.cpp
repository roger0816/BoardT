#include "DialogPainter.h"
#include "ui_DialogPainter.h"

DialogPainter::DialogPainter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPainter)
{
    ui->setupUi(this);

    m_btns.addButton(ui->btnBlack);
    ui->btnBlack->setChecked(true);
    m_btns.addButton(ui->btnGray);
    m_btns.addButton(ui->btnRed);
    m_btns.addButton(ui->btnGreen);
    m_btns.addButton(ui->btnBlue);
    m_btns.addButton(ui->btnWhite);

    foreach(QAbstractButton *btn,m_btns.buttons())
    {
        connect(btn,&QAbstractButton::clicked,this,&DialogPainter::colorClicked);
    }


    ui->btnS->setChecked(true);

    connect(ui->btnS,&QAbstractButton::clicked,this,&DialogPainter::sizeClicked);

    connect(ui->btnM,&QAbstractButton::clicked,this,&DialogPainter::sizeClicked);

    connect(ui->btnL,&QAbstractButton::clicked,this,&DialogPainter::sizeClicked);

    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    setMouseTracking(true);
    //setWindowFlags(Qt::WindowCloseButtonHint);
}

DialogPainter::~DialogPainter()
{
    delete ui;
}

void DialogPainter::colorClicked()
{

    foreach(QAbstractButton *btn,m_btns.buttons())
    {
        btn->setChecked(false);

    }

    QPushButton *btn = dynamic_cast<QPushButton*>(sender());

    btn->setChecked(true);

    if(btn== ui->btnBlack)
    {
        ui->wContent->setRgb(0,0,0);
    }
    else if(btn== ui->btnGray)
    {

        ui->wContent->setRgb(80,80,80);
    }
    else if(btn== ui->btnRed)
    {
        ui->wContent->setRgb(255,0,0);
    }
    else if(btn== ui->btnGreen)
    {
        ui->wContent->setRgb(0,255,0);
    }
    else if(btn== ui->btnBlue)
    {
        ui->wContent->setRgb(0,0,255);
    }
    else if(btn== ui->btnWhite)
    {
        ui->wContent->setRgb(255,255,255);
    }

}

void DialogPainter::sizeClicked()
{
    ui->btnL->setChecked(false);

    ui->btnM->setChecked(false);

    ui->btnS->setChecked(false);

    QPushButton *btn = dynamic_cast<QPushButton*>(sender());

    btn->setChecked(true);

    int iSize = 2;

    if(btn == ui->btnL)
        iSize = 6;
    else if(btn == ui->btnM)
        iSize = 4;

    ui->wContent->setPwidth(iSize);

}



//
CPainter::CPainter(QWidget *parent)
{
    m_color.setRgb(0,0,0);
}

CPainter::~CPainter()
{

}

void CPainter::setRgb(int r, int g, int b)
{
    m_color.setRgb(r,g,b);

    update();
}

void CPainter::setPwidth(int i)
{
    m_iPsize = i;

    update();
}

void CPainter::paintEvent(QPaintEvent *)
{
    QPen pen;

    pen.setWidth(m_iPsize);

    pen.setColor(m_color);

    QPainter pp(&pix);

    pp.setPen(pen);
    pp.drawLine(lastPoint,endPoint);
    lastPoint=endPoint;

    QPainter painter(this);

    painter.drawPixmap(0,0,pix);
}


void CPainter::mousePressEvent(QMouseEvent *event)
{
   // if(event->button()==Qt::LeftButton){

        lastPoint=event->pos();
    //}
}


void CPainter::mouseMoveEvent(QMouseEvent *event)
{
   // if(event->buttons()&Qt::LeftButton)
    //{
        endPoint=event->pos();
        update();

    //}
}

void CPainter::showEvent(QShowEvent *)
{

    pix=QPixmap(width(),height());

    pix.fill(Qt::white);
}

void CPainter::resizeEvent(QResizeEvent *)
{
    pix=QPixmap(width(),height());

    pix.fill(Qt::white);
}


void CPainter::mouseReleaseEvent(QMouseEvent *event){
   // if(event->button()==Qt::LeftButton)
 //   {
        endPoint=event->pos();
        update();
   // }
}

void DialogPainter::on_btnCancel_clicked()
{
    reject();
}

void DialogPainter::on_btnSend_clicked()
{
    ui->wContent->pix.save(m_sSavePath+".png");

    done(0);
}
