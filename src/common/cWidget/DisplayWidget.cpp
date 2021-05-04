#include "DisplayWidget.h"
#include "ui_DisplayWidget.h"

DisplayWidget::DisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWidget)
{
    ui->setupUi(this);

    m_fDiff = 0.50;

    QSize baseSize(1080,1920);

    this->resize(baseSize*m_fDiff);


}

DisplayWidget::~DisplayWidget()
{
    delete ui;
}

QPixmap DisplayWidget::setLayer(QString sPath)
{
    qDebug()<<"layer path : "<<m_sPath;

    m_sPath = sPath;

    m_layerName = m_sPath.split("/").last();

    CDATA.m_sCurrentLayerName = m_layerName;

    LayerData *layerData = CDATA.m_dData[m_layerName] ;

    qDeleteAll(m_listItem);

    m_listItem.clear();

    if(layerData==nullptr)
        return QPixmap();


    ui->wBg->setStyleSheet("QWidget#"+ui->wBg->objectName()+"{border-image:url("+layerData->m_sBgPath+");}");

    QList<ObjData* > listData = layerData->m_listData;

    for(int i=0;i<listData.length();i++)
    {

        ItemBaseContent *item = new ItemBaseContent(ui->wBg);

        connect(item,&ItemBaseContent::sendFocus,this,&DisplayWidget::slotFocus);

        connect(item,&ItemBaseContent::sendUpdate,this,&DisplayWidget::slotUpdate);


        item->setData(listData[i],m_fDiff);

        item->m_wBg->setStyleSheet("background-color:green;");

        item->setEdit(false);

        item->show();

        m_listItem.append(item);
    }



    CDATA.m_dData[m_sPath.split("/").last()]->m_scaleImage = this->grab();


    return CDATA.m_dData[m_sPath.split("/").last()]->m_scaleImage;
}

void DisplayWidget::setEdit(bool b)
{
    m_bEdit = b;

    foreach(ItemBaseContent *t,m_listItem)
    {
        t->setEdit(b);
    }
}

void DisplayWidget::resizeEvent(QResizeEvent *)
{
    updateItemRect();
}

void DisplayWidget::showEvent(QShowEvent *)
{
    updateItemRect();
}

void DisplayWidget::updateItemRect()
{

    float iW = height()*1080/1920;

    setMinimumWidth(iW);

    setMaximumWidth(iW);

    m_fDiff = iW/1080;

    foreach(ItemBaseContent *item ,m_listItem)
    {
        item->m_diffSize = m_fDiff;

        item->updateItem();
    }

}

bool DisplayWidget::checkObjName(QString sObj)
{
    bool b = true;


    LayerData *layerData = CDATA.m_dData[m_layerName] ;

    if(layerData == nullptr)
        return false;


    for(int i=0;i<layerData->m_listData.length();i++)
    {
        if(layerData->m_listData.at(i)->m_sName == sObj)
            b = false;


    }


    return b;

}

void DisplayWidget::slotFocus()
{
    if(!m_bEdit)
        return;


    ItemBaseContent *target = dynamic_cast<ItemBaseContent*>(sender());

    QString sPath="";

    for(int i=0;i<m_listItem.length();i++)
    {
        if(target==m_listItem[i])
        {
            sPath = m_listItem[i]->m_sPath;
        }
        else
        {
            m_listItem[i]->setRoll(false);
        }
    }


    if(sPath!="")
        emit changeTarget(sPath);

}

void DisplayWidget::slotUpdate()
{
    ItemBaseContent *target = dynamic_cast<ItemBaseContent*>(sender());

    qDebug()<<"slot Update ";
    emit changeTarget(target->m_sPath);
}

void DisplayWidget::refreshItem()
{


    foreach(ItemBaseContent *item ,m_listItem)
    {
        item->updateItem();
    }



    LayerData *layerData = CDATA.m_dData[m_layerName] ;

    if(layerData==nullptr)
        return ;

    ui->wBg->setStyleSheet("QWidget#"+ui->wBg->objectName()+"{border-image:url("+layerData->m_sBgPath+");}");

}

void DisplayWidget::raiseItem(QString sPath)
{
    foreach(ItemBaseContent *item ,m_listItem)
    {
        if(item->m_sPath == sPath)
            item->raise();
    }
}

void DisplayWidget::renameItem(QString sOldPath, QString sNewPath)
{
    foreach(ItemBaseContent *item ,m_listItem)
    {

        if(item->m_sPath == sOldPath)
        {
            item->m_sPath = sNewPath;

            item->m_sName = sNewPath.split("/").last();

        }
        //
    }
}

void DisplayWidget::deleteItem(QString sPath)
{
    QStringList listTmp = sPath.split("/");

    QString sObjName = listTmp.last();

    if(listTmp.length()<2)
        return ;

    listTmp.pop_back();
    QString sLayer = listTmp.last();

    bool bOk;


    CDATA.m_dData[sLayer]->m_listData.removeOne(CDATA.getObj(sLayer, sObjName,bOk));

    int iIdx =-1;

    for(int i=0;i<m_listItem.length();i++)
    {
        if(m_listItem[i]->m_sName == sObjName)
        {
            iIdx =i;

        }
    }

    if(iIdx>=0 && iIdx <m_listItem.length())
    {
        m_listItem[iIdx]->hide();

        m_listItem.removeAt(iIdx);
    }

    qDebug()<<m_listItem.length();

}

void DisplayWidget::addItem(int iIdx)
{

    LayerData *layerData = CDATA.m_dData[m_layerName] ;

    if(layerData == nullptr)
        return;


    ObjData * obj = new ObjData(this);

    QString sTmp = "TEXT_%1";



    if(iIdx == ADD_BTN_PIC)
    {
        obj->m_sType = E_PIC;

        sTmp = "PIC_%1";

    }

    else if(iIdx == ADD_BTN_VIDEO)
    {
        obj->m_sType = E_VIDEO;

        sTmp = "VIDEO_%1";

    }

    else if(iIdx == ADD_BTN_BTN)
    {
        obj->m_sType = E_BUTTON;

        obj->m_dataText.sText="BUTTON";

        sTmp = "BUTTON_%1";

    }

    else if(iIdx == ADD_BTN_MARQUEE)
    {
        obj->m_sType = E_BUTTON;

        obj->m_dataText.sText="BUTTON";

        sTmp = "MARQUEE%1";
    }
    else //(iIdx == ADD_BTN_TEXT)
    {
        obj->m_sType = E_TEXT;

        sTmp = "TEXT_%1";

    }


    bool b = false;

    int i = 0;


    int iRetryCount =0;

    QString sName;

    while(!b && iRetryCount <20)
    {
        sName = sTmp.arg(i);


        b = checkObjName(sName);

        iRetryCount++;

        i++;
    }

    if(iRetryCount>=20)
        return ;

    obj->setPath(m_sPath+"/"+sName);

    layerData->m_listData.append(obj);

    ItemBaseContent *item = new ItemBaseContent(ui->wBg);

    connect(item,&ItemBaseContent::sendFocus,this,&DisplayWidget::slotFocus);

    connect(item,&ItemBaseContent::sendUpdate,this,&DisplayWidget::slotUpdate);

    item->setData(layerData->m_listData.last(),m_fDiff);

    item->m_wBg->setStyleSheet("background-color:green;");

    item->setEdit(true);

    item->show();

    m_listItem.append(item);
}
