#include "DialogPop.h"
#include "ui_DialogPop.h"

DialogPop::DialogPop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogPop)
{
    ui->setupUi(this);

    m_listBtn<<ui->btn0<<ui->btn1<<ui->btn2
            <<ui->btn3<<ui->btn4<<ui->btn5
           <<ui->btn6<<ui->btn7<<ui->btn8;

    for(int i=0;i<m_listBtn.length();i++)
    {
        connect(m_listBtn[i],&QPushButton::clicked,this,&DialogPop::btnClicked);
    }


    connect(ui->wPopBg,&WidgetBg::clicked,this,&DialogPop::hide);

}

DialogPop::~DialogPop()
{
    delete ui;
}

void DialogPop::setPicRun(QStringList listPath, QRect rect)
{
    m_listPicPath = listPath;

    m_listUrl.clear();

    ui->widget->resize(800,800);

    ui->widget->move(150,200);

    displayInfo();

}

void DialogPop::setActionRun(QStringList listPath, QStringList listUrl, QRect rect)
{
    m_listPicPath = listPath;

    m_listUrl = listUrl;

    qDebug()<<"BB : "<<m_listUrl;

    ui->widget->resize(800,800);

    ui->widget->move(150,200);

    displayInfo();
}

void DialogPop::setQrCode(QString sText, QRect rect)
{

    ui->widget->resize(320,320);

    ui->widget->move(400,200);



    QRecLevel level = QR_ECLEVEL_H;

    QRencodeMode mode = QR_MODE_8;

    QByteArray bsharecode = sText.toUtf8();

    QRcode *code = QRcode_encodeString(sText.toLatin1(), 7, level, mode, 1);

    QPixmap pix = drawImageQr(code);

    ui->lbQr->setStyleSheet("background-color:white");

    ui->lbQr->setPixmap(pix);

    ui->stackedWidget->setCurrentWidget(ui->pageQr);

    show();


}

void DialogPop::setBg(QString sFilePath)
{
    ui->widget->setObjectName("popBg");
    ui->widget->setStyleSheet("QWidget#popBg{border-image:url(\""+sFilePath+"\");}");

}

QPixmap DialogPop::drawImageQr(QRcode *code)
{

    unsigned char *point = code->data;

    double scale = 256* 1.0/ code->width;

    QPixmap pixmap(280,280);

    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor("#000000")));

    for (int y = 0; y < code->width; y ++)
    {
        for (int x = 0; x < code->width; x ++)
        {
            if (*point & 1)
            {
                QRectF r(x * scale+15, y * scale+15, scale, scale);
                painter.drawRects(&r, 1);
            }
            point ++;
        }
    }

    return pixmap;

}

void DialogPop::displayInfo()
{


    foreach(QPushButton *btn ,m_listBtn)
    {
        btn->setStyleSheet("border-image:url()");
    }


    for(int i=0;i<m_listBtn.length();i++)
    {
        if(i<m_listPicPath.length())
        {
            m_listBtn[i]->setStyleSheet("border-image:url(\""+m_listPicPath.at(i)+"\");");

        }
    }

    ui->stackedWidget->setCurrentWidget(ui->pagePicRun);


    show();
}

void DialogPop::on_btnBack_clicked()
{
    emit sendTouchLock();

    if(ui->stackedWidget->currentWidget() == ui->pageShowPic ||
            ui->stackedWidget->currentWidget() == ui->pageWeb)
        ui->stackedWidget->setCurrentWidget(ui->pagePicRun);
    else
    {
        hide();
    }
}

void DialogPop::btnClicked()
{
    emit sendTouchLock();

    QPushButton *btn = dynamic_cast<QPushButton*>(sender());

    int iIdx = m_listBtn.indexOf(btn);

    if(m_listUrl.length()<1)
    {
        if(iIdx<m_listPicPath.length() && iIdx>=0)
        {
            ui->lbPic->setStyleSheet("border-image:url(\""+m_listPicPath.at(iIdx)+"\");");

            ui->stackedWidget->setCurrentWidget(ui->pageShowPic);
        }
    }
    else
    {
        if(iIdx<m_listUrl.length() && iIdx>=0)
        {
            ui->wWeb->loadUrl(m_listUrl.at(iIdx));

            ui->stackedWidget->setCurrentWidget(ui->pageWeb);
        }
    }
}

void WidgetBg::mousePressEvent(QMouseEvent *)
{
    emit clicked();
}
