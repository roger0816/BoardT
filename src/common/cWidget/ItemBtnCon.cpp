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
          ui->btn->setStyleSheet(sStyle.arg(txtColor.red())
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
      ui->btn->setStyleSheet(sStyle.arg(txtColor.red())
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

      ui->btn->setFont(f);


    ui->btn->setText(m_data.value(Label::text).toString());

//    if(m_data.bIsCent)
//        ui->btn->setAlignment(Qt::AlignCenter);
//    else
//        ui->btn->setAlignment(Qt::AlignLeading);
}

ItemBtnCon::~ItemBtnCon()
{
    delete ui;
}
