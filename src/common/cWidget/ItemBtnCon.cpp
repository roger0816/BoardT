#include "ItemBtnCon.h"
#include "ui_ItemBtnCon.h"

ItemBtnCon::ItemBtnCon(QWidget *parent) :
    ItemBaseObj(parent),
    ui(new Ui::ItemBtnCon)
{
    ui->setupUi(this);
}



void ItemBtnCon::updateItem()
{
    if(m_obj==nullptr)
        return;

    qDebug()<<"update btn item";

    DataText m_data;
        m_data = m_obj->m_dataText;

    QColor bgColor = m_data.bgColor;

    QColor txtColor = m_data.textColor;


    QString sStyle = "color:rgba(%1,%2,%3,%4);"
                     "background-color:rgba(%5,%6,%7,%8);";


    if(m_data.m_sImagePath.trimmed()!="")
    {
        ui->btn->setStyleSheet(sStyle.arg(m_data.textColor.red())
                                 .arg(m_data.textColor.green())
                                 .arg(m_data.textColor.blue())
                                 .arg(m_data.textColor.alpha())
                                 .arg(0)
                                 .arg(0)
                                 .arg(0)
                                 .arg(0)
                                 +" border-image:url("+m_data.m_sImagePath+");");


    }
    else
    {
    ui->btn->setStyleSheet(sStyle.arg(m_data.textColor.red())
                      .arg(m_data.textColor.green())
                      .arg(m_data.textColor.blue())
                      .arg(m_data.textColor.alpha())
                      .arg(m_data.bgColor.red())
                      .arg(m_data.bgColor.green())
                      .arg(m_data.bgColor.blue())
                      .arg(m_data.bgColor.alpha())
                        );
    }

    QFont f = m_data.font;

    f.setPixelSize(f.pixelSize()*m_diffSize);

    ui->btn->setFont(f);

    ui->btn->setText(m_data.sText);

//    if(m_data.bIsCent)
//        ui->btn->setAlignment(Qt::AlignCenter);
//    else
//        ui->btn->setAlignment(Qt::AlignLeading);
}

ItemBtnCon::~ItemBtnCon()
{
    delete ui;
}
