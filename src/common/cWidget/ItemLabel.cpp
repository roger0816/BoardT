#include "ItemLabel.h"
#include "ui_ItemLabel.h"

ItemLabel::ItemLabel(QWidget *parent) :
    ItemBaseObj(parent),
    ui(new Ui::ItemLabel)
{
    ui->setupUi(this);

    m_lb = ui->label;
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
          m_data = m_obj->m_data;



      QColor bgColor = m_data.value(Label::bgColor,"#ffffffff").toString();
      //bgColor.name(QColor::HexArgb)


      QColor txtColor = m_data.value(Label::txtColor,"#ff000000").toString();

    QString sImagePath = m_data.value(Label::imagePath).toString();

      QString sStyle = "color:rgba(%1,%2,%3,%4);"
                       "background-color:rgba(%5,%6,%7,%8);";

      if(sImagePath.trimmed()!="")
      {
          ui->label->setStyleSheet(sStyle.arg(txtColor.red())
                                   .arg(txtColor.green())
                                   .arg(txtColor.blue())
                                   .arg(txtColor.alpha())
                                   .arg(0)
                                   .arg(0)
                                   .arg(0)
                                   .arg(0)
                                   +" border-image:url("+sImagePath+");");


      }
      else
      {
      ui->label->setStyleSheet(sStyle.arg(txtColor.red())
                        .arg(txtColor.green())
                        .arg(txtColor.blue())
                        .arg(txtColor.alpha())
                        .arg(bgColor.red())
                        .arg(bgColor.green())
                        .arg(bgColor.blue())
                        .arg(bgColor.alpha())
                          );
      }



      QFont f ;
      f.fromString("Arial,24,-1,5,50,0,0,0,0,0,Regular");

      QString sFont = m_data.value(Label::font,"Arial,24,-1,5,50,0,0,0,0,0,Regular").toString();

      f.fromString(sFont);

     // f.setPixelSize(f.pixelSize()*m_diffSize);

      ui->label->setFont(f);


      ui->label->setText(m_data.value(Label::text,"文字").toString());

      if(m_data.value(Label::alignCenter).toInt(),1)
          ui->label->setAlignment(Qt::AlignCenter);
      else
          ui->label->setAlignment(Qt::AlignLeading);



}
