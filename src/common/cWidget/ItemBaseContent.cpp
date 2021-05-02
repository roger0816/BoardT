#include "ItemBaseContent.h"
#include "ui_ItemBaseContent.h"


ItemBaseContent::ItemBaseContent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemBaseContent)
{
    ui->setupUi(this);

    m_wBg = ui->wBg;

    // m_wBg->setStyleSheet("background-color:red;");

    m_lay = new QGridLayout;

    m_lay->setSpacing(0);

    m_lay->setMargin(0);

    m_wBg->setLayout(m_lay);

    m_touch = new ItemEditTouch(this);

    m_touch->setObjectName("m_itemTouch_");

    connect(m_touch,&ItemEditTouch::sendMouse,this,&ItemBaseContent::slotMouseEvent);

    m_touch->hide();

}

ItemBaseContent::~ItemBaseContent()
{
    delete ui;
}

void ItemBaseContent::setData(ObjData *obj, float diffSize)
{

    m_obj = obj;

    m_diffSize = diffSize;

    m_sType = obj->m_sType;

    m_sPath = obj->m_sObjPath;

    QStringList listTmp = m_sPath.split("/");

    m_sName = listTmp.last();

    if(listTmp.length()>2)
    {
        m_sLayerName = listTmp.at(listTmp.length()-2);

        m_sModelName = listTmp.at(listTmp.length()-3);
    }



    updateItem();

    qDebug()<<"type : "<<obj->m_sType;


    while(m_lay->count()>0)
    {

        m_lay->removeItem(m_lay->takeAt(0));

    }

    if(m_sType == E_TEXT)
    {

        itemLabel = new ItemLabel(m_wBg);
    }

    else if(m_sType == E_PIC)
    {
        itemLabel = new ItemPicCon(m_wBg);
    }

    itemLabel->m_diffSize = m_diffSize;

    itemLabel->setData(obj);

    itemLabel->show();

    m_lay->addWidget(itemLabel);

    m_wBg->setLayout(m_lay);





}

void ItemBaseContent::setRoll(bool b)
{
    m_bRoll = b;

    m_touch->setRoll(b);


    if(m_bRoll)
    {

        m_touch->raise();

        emit sendFocus();

    }


}

void ItemBaseContent::setEdit(bool b)
{
    m_bEdit = b;

    m_touch->setVisible(b);
}

void ItemBaseContent::updateItem()
{

    QRect rectT;

    if(m_obj!=nullptr)
        rectT = m_obj->m_rect;


    QRect r;

    r.setX( rectT.x()*m_diffSize);

    r.setY(rectT.y()*m_diffSize);

    r.setWidth(rectT.width()*m_diffSize);

    r.setHeight(rectT.height()*m_diffSize);

    setGeometry(r);


    if(m_sType == E_TEXT && itemLabel!=nullptr)
    {

        itemLabel->m_diffSize = m_diffSize;

        itemLabel->updateItem();


    }



}



void ItemBaseContent::resizeEvent(QResizeEvent *)
{
    m_touch->resize(size());

    m_touch->raise();
}

void ItemBaseContent::slotMouseEvent(QMouseEvent *e)
{
    if(e->type() == QMouseEvent::MouseButtonPress)
    {
        //    if(!m_bEdit)
        //        return ;

        m_bMove = false;

        setRoll(true);

        if(e->x()>width()-16 && e->y() > height()-16)
        {
            m_bChangeSize = true;
        }
        else
        {
            m_bChangeSize = false;
        }

        m_preP = e->pos();

        m_preSize = size();
    }
    else if(e->type() == QMouseEvent::MouseButtonRelease)
    {
        if(m_bMove)
        {
            QStringList listTmp = m_sPath.split("/");

            if(listTmp.length()>2)
            {
                listTmp.pop_back();

                listTmp.pop_back();
            }


            qDebug()<<"model : "<<m_sModelName<<" ,layer: "<<m_sLayerName<<" ,obj: "<<m_sName;

            bool bOk = false;

            ObjData* obj = CDATA.getObj(m_sLayerName,m_sName,bOk);


            if(bOk)
            {

                obj->m_rect = QRect(x()/m_diffSize,y()/m_diffSize,width()/m_diffSize,height()/m_diffSize);

            }

            emit sendUpdate();
        }
    }

    else if(e->type() == QMouseEvent::MouseMove)
    {
        m_bMove = true;

        QPoint move = e->pos()-m_preP;

        QPoint af = this->pos()+move;

        if(!m_bChangeSize)
        {
            this->move(af);
        }
        else
        {

            QSize t(m_preSize+QSize(move.x(),move.y()));
            int iW = qBound(40,t.width(),this->parentWidget()->width()+10);

            int iH = qBound(40,t.height(),this->parentWidget()->height()+10);

            resize(iW,iH);
        }
    }
}

