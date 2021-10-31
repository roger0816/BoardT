#include "ItemBtnCon.h"
#include "ui_ItemBtnCon.h"


ItemBtnCon::ItemBtnCon(QWidget *parent) :
    ItemLabel(parent),
    ui(new Ui::ItemBtnCon)
{
    //   ui->setupUi(this);


}


ItemBtnCon::~ItemBtnCon()
{
    delete ui;
}

void ItemBtnCon::setLbStyle(QString sTxtColorKey, QString sBgColorKey, QString sImagePathKey, QString sFontKey, QString sCentKey)
{
    ItemLabel::setLbStyle(sTxtColorKey,sBgColorKey,sImagePathKey,sFontKey,sCentKey);

    m_lb->setAlignment(Qt::AlignCenter);


    QString sT=
            " border-style: outset; "
            " border-radius: 12px; "
            " border-width: 5px; "
            " padding:1px; "
            " border-color: #99b3d3; "
            " }"
            ;

    //           border-style: outset;
    //           border-radius: 10px;
    //           padding:0px;

    //           border-color: #99b3d3;
    QString sCurrentStyle = m_lb->styleSheet();

    if(sCurrentStyle.right(1)== "}" )
        sCurrentStyle.remove(sCurrentStyle.length()-1,1);

    m_lb->setStyleSheet(sCurrentStyle+sT);

}

void ItemBtnCon::mousePressEvent(QMouseEvent *)
{

    if(m_obj!=nullptr)
    {
       m_lb->setText(m_data[Btn::btnText2].toString());

    }

    QString sT=
            " border-style: outset; "
            " border-radius: 12px; "
            " border-width: 4px; "
            " padding:1px; "
            " border-color: #99b3d3; "
            " }"
            ;



    QString sCurrentStyle = m_lb->styleSheet();

    if(sCurrentStyle.right(1)== "}" )
        sCurrentStyle.remove(sCurrentStyle.length()-1,1);

    m_lb->setStyleSheet(sCurrentStyle+sT);
}

void ItemBtnCon::mouseReleaseEvent(QMouseEvent *)
{

    if(m_obj!=nullptr)
    {
        m_lb->setText(m_obj->m_data[Label::text].toString());

    }

    QString sT=
            " border-style: outset; "
            " border-radius: 12px; "
            " border-width: 8px; "
            " padding:1px; "
            " border-color: #99b3d3; "
            " }"
            ;


    QString sCurrentStyle = m_lb->styleSheet();

    if(sCurrentStyle.right(1)== "}" )
        sCurrentStyle.remove(sCurrentStyle.length()-1,1);

    m_lb->setStyleSheet(sCurrentStyle+sT);


    if(m_data[Btn::btnType].toInt()==1 && m_data[Btn::btnTypeNote]!="")
    {
        //change page

        QString sLayerName = m_data[Btn::btnTypeNote].toString();

          qDebug()<<"AAA0";
        CCTRL.changeLayer(sLayerName);


    }

}

