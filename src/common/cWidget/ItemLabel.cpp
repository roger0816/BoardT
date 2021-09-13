#include "ItemLabel.h"
#include "ui_ItemLabel.h"

ItemLabel::ItemLabel(QWidget *parent) :
    ItemBaseObj(parent),
    ui(new Ui::ItemLabel)
{
    ui->setupUi(this);

    m_lb = ui->label;

    m_lb->setObjectName("m_lb");
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



      ui->label->setStyleSheet("QLabel#"+ui->label->objectName()+"{color:"+getStyleSheetRgba(m_data.value(Label::txtColor,"#000000ff").toString())
                               +";background-color:"+getStyleSheetRgba(m_data.value(Label::bgColor,"#ffffffff").toString())+"}");



    QString sImagePath = m_data.value(Label::imagePath).toString();


      if(sImagePath.trimmed()!="")
      {
          ui->label->setStyleSheet(ui->label->styleSheet()
                                   +" border-image:url("+sImagePath+");");


      }




      QFont f ;
      f.fromString("Arial,24,-1,5,50,0,0,0,0,0,Regular");

      QString sFont = m_data.value(Label::font,"Arial,24,-1,5,50,0,0,0,0,0,Regular").toString();

      f.fromString(sFont);

     // f.setPixelSize(f.pixelSize()*m_diffSize);

      ui->label->setFont(f);


      ui->label->setText(m_data.value(Label::text,"文字").toString());

      qDebug()<<"update alignCenter : "<<m_data.value(Label::alignCenter).toInt();
      if(m_data.value(Label::alignCenter).toInt())
          ui->label->setAlignment(Qt::AlignCenter);
      else
          ui->label->setAlignment(Qt::AlignLeading);



}
