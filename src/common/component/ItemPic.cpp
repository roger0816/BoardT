#include "ItemPic.h"

ItemPic::ItemPic(QWidget *parent) : ItemBase(parent)
{
    m_lb = new QLabel(this);
}

bool ItemPic::init()
{

    bool b = false;
    QFileInfoList list = QDir(m_sPath).entryInfoList(QStringList()<<"*.png"<<".jpg"<<"*.PNG"<<"*.JPG");

    if(list.length()>0)
    {
        setPic(list.first().filePath());

        b = true;
    }

    return b;
}
void ItemPic::setPic(QString sFilePath)
{

    QString sStyle = "border-image:url(\""+sFilePath+"\");";

    m_lb->setStyleSheet(sStyle);
}

void ItemPic::setText(QString sText)
{
    m_lb->setText(sText);
}

void ItemPic::resizeEvent(QResizeEvent *)
{
    m_lb->resize(size());

    m_lb->move(0,0);
}
