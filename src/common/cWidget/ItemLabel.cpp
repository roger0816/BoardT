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

    setLbStyle(Label::txtColor,Label::bgColor,Label::imagePath,Label::font,Label::alignCenter);



}

void ItemLabel::setLbStyle(QString sTxtColorKey, QString sBgColorKey, QString sImagePathKey, QString sFontKey, QString sCentKey)
{

    QString sTxtColor =getStyleSheetRgba(m_data.value(sTxtColorKey,"#000000ff").toString());

    QString sBg = getStyleSheetRgba(m_data.value(sBgColorKey,"#ffffffff").toString());


    QString sImagePath =  m_data.value(sImagePathKey).toString();



    if(sImagePath.trimmed()!="")
    {

        sBg="";

        QString sImage = QApplication::applicationDirPath()+sImagePath;

        if(!QFile(sImage).exists())
            sImage = m_data["originImage"].toString();


        ui->label->setStyleSheet("QLabel#"+ui->label->objectName()+"{color:"+sTxtColor
                                 +";background-color:rgba(0, 0, 0,0);"
                                 ";border-image:url("+sImage+");}");


    }
    else
    {
        ui->label->setStyleSheet("QLabel#"+ui->label->objectName()+"{color:"+sTxtColor
                                 +";background-color:"+sBg+"}");

        qDebug()<<"AAAA : "<<sTxtColor<<" , "<<sBg;

    }


    QFont f ;
    f.fromString("Arial,24,-1,5,50,0,0,0,0,0,Regular");

    QString sFont = m_data.value(sFontKey,"Arial,24,-1,5,50,0,0,0,0,0,Regular").toString();

    f.fromString(sFont);

#ifndef Q_OS_WINDOWS
    f.setPointSize(f.pointSize()*2.2);
#endif
    ui->label->setFont(f);


    ui->label->setText(m_data.value(Label::text,"文字").toString());
    qDebug()<<m_data.value(Label::text,"文字").toString();
    qDebug()<<"update alignCenter : "<<m_data.value(sCentKey).toInt();
    if(m_data.value(Label::alignCenter).toInt())
        ui->label->setAlignment(Qt::AlignCenter);
    else
        ui->label->setAlignment(Qt::AlignLeading);


}
