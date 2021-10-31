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


    m_click = new ItemClickTouch(this);

    connect(m_click,&ItemClickTouch::sendPress,this,&ItemBaseContent::slotPress);


    m_click->setObjectName("m_itemClick");

    m_click->show();

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



    while(m_lay->count()>0)
    {

        m_lay->removeItem(m_lay->takeAt(0));

    }

    if(m_sType == E_TEXT)
    {
        qDebug()<<"Text type";
        itemLabel = new ItemLabel(m_wBg);
    }

    else if(m_sType == E_PIC)
    {
        itemLabel = new ItemPicCon(m_wBg);
    }

    else if(m_sType == E_VIDEO)
    {
        itemLabel = new ItemVideoCon(m_wBg);
    }

    else if(m_sType == E_BUTTON)
    {

        itemLabel = new ItemBtnCon(m_wBg);
    }
    else if(m_sType == E_MARQUEE)
    {

        itemLabel = new ItemMarCon(m_wBg);
    }
    else if(m_sType == E_QRCODE)
    {

        itemLabel = new ItemQrCon(m_wBg);
    }

    else if(m_sType == E_TXVALUE)
    {

        itemLabel = new ItemTxObjCon(m_wBg);
    }
    else if(m_sType == E_DATETIME)
    {

        itemLabel = new ItemDateTime(m_wBg);
    }

    else if(m_sType == E_URL)
    {

        itemLabel = new ItemUrl(m_wBg);
    }

    else if(m_sType == E_GRID)
    {

        itemLabel = new ItemGrid(m_wBg);
    }
    else
    {
        itemLabel = new ItemLabel(m_wBg);
        m_sType = E_TEXT;
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

    m_click->setVisible(!b);

    if(m_sType==E_BUTTON || m_sType==E_GRID || m_sType==E_URL)
    {
        m_click->hide();
    }

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


    if(itemLabel!=nullptr)
    {

        itemLabel->m_diffSize = m_diffSize;

        itemLabel->updateItem();


    }



}



void ItemBaseContent::resizeEvent(QResizeEvent *)
{
    m_touch->resize(size());

    m_touch->raise();

    m_click->resize(size());

    m_click->raise();
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

void ItemBaseContent::slotPress(QMouseEvent *e)
{
    if(m_obj == nullptr)
        return;


    QString sCmd = m_obj->m_dataCmd.sCmd;

    QString sValue1 = m_obj->m_dataCmd.sValue1;

    QString sValue2 = m_obj->m_dataCmd.sValue2;

    if(sCmd == CMD_Page || sCmd == CMD_PageNoStop)
    {

        QString sApp = QApplication::applicationDirPath()+"/ActiveTools.exe "+CMD_Page+" "+sValue1+" "+sValue2;
    //    system(sApp.toStdString().c_str());


        QProcess p;

        p.setWorkingDirectory(QApplication::applicationDirPath());

        p.startDetached(sApp);
   // p.start(sApp);

    }

}

