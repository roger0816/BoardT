#include "ItemLabel.h"
#include "ui_ItemLabel.h"

ItemLabel::ItemLabel(QWidget *parent) :
    ItemBaseObj(parent),
    ui(new Ui::ItemLabel)
{
    ui->setupUi(this);
}

ItemLabel::~ItemLabel()
{
    delete ui;
}

void ItemLabel::init()
{
    updateItem();
}




void ItemLabel::updateItem()
{
    if(m_obj!=nullptr)
        m_data = m_obj->m_dataText;

    QColor bgColor = m_data.bgColor;

    QColor txtColor = m_data.textColor;


    QString sStyle = "color:rgba(%1,%2,%3,%4);"
                     "background-color:rgba(%5,%6,%7,%8);";


    if(m_data.m_sImagePath.trimmed()!="")
    {
        ui->label->setStyleSheet(sStyle.arg(m_data.textColor.red())
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
    ui->label->setStyleSheet(sStyle.arg(m_data.textColor.red())
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

    ui->label->setFont(f);

    ui->label->setText(m_data.sText);

    if(m_data.bIsCent)
        ui->label->setAlignment(Qt::AlignCenter);
    else
        ui->label->setAlignment(Qt::AlignLeading);

}
