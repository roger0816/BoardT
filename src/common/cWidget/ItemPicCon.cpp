#include "ItemPicCon.h"
#include "ui_ItemPicCon.h"

ItemPicCon::ItemPicCon(QWidget *parent) :
    ItemBaseObj(parent),
    ui(new Ui::ItemPicCon)
{
    ui->setupUi(this);

    startTimer(1000);

}

ItemPicCon::~ItemPicCon()
{
    delete ui;
}

void ItemPicCon::updateItem()
{
    m_iSecCount = 9;
}

void ItemPicCon::timerEvent(QTimerEvent *)
{
    m_iSecCount++;

    int iSec = 10;

    if(m_obj!=nullptr && m_obj->m_dataPic.listPic.length()>0)
    {
        iSec = m_obj->m_dataPic.iSec;


        if(m_iSecCount%iSec==0)
        {
            if(m_iIdx>= m_obj->m_dataPic.listPic.length())
                m_iIdx = 0;

           // ui->label->setPixmap(m_obj->m_dataPic.listPic.at(m_iIdx));

            QPixmap p =m_obj->m_dataPic.listPic.at(m_iIdx);


            ui->label->setPixmap(p.scaled(ui->label->size()));

            m_iIdx++;

        }



    }

}

