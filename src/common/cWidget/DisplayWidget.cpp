#include "DisplayWidget.h"
#include "ui_DisplayWidget.h"

DisplayWidget::DisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWidget)
{
    ui->setupUi(this);

    m_fDiff = 0.50;

    ui->wBg->setObjectName("Display_wBg");

    QSize baseSize(1080,1920);

    this->resize(baseSize*m_fDiff);


}

DisplayWidget::~DisplayWidget()
{
    delete ui;
}

QPixmap DisplayWidget::setLayer(QString sPath, int iVideoStatus)
{

    m_sPath = sPath;

    qDebug()<<"layer path : "<<m_sPath<<",video status :  "<<iVideoStatus;

    if(iVideoStatus == 0)
    {
        if(m_video!=nullptr)
        {

            m_video->m_player->stop();

            m_video->hide();
        }

    }


    m_layerName = m_sPath.split("/").last();

    CDATA.m_sCurrentLayerName = m_layerName;

    LayerData *layerData = CDATA.m_dData[m_layerName] ;

    qDeleteAll(m_listItem);

    m_listItem.clear();

    if(layerData==nullptr)
        return QPixmap();


    refreshBg();

    QList<ObjData* > listData = layerData->m_listData;

    for(int i=0;i<listData.length();i++)
    {

        ItemBaseContent *item;

        item = new ItemBaseContent(ui->wBg);

        connect(item,&ItemBaseContent::sendFocus,this,&DisplayWidget::slotFocus);

        connect(item,&ItemBaseContent::sendUpdate,this,&DisplayWidget::slotUpdate);

        item->setData(listData[i],m_fDiff);

       // item->m_wBg->setStyleSheet("background-color:green;");

        item->setEdit(false);

        item->show();

        m_listItem.append(item);

        if(listData[i]->m_sType == E_VIDEO && iVideoStatus ==0)
        {

            qDebug()<<"video set ";
            if(m_video == nullptr)
            {
                m_video = new ItemPlayer(this);
            }

            m_video->show();

            m_video->setPlayList(listData[i]->m_dataVideo.listName);

            m_video->setMute(listData[i]->m_dataVideo.bIsMute);

            m_video->resize(item->size());

            m_video->move(item->pos());

            m_video->setHidden(m_bEdit);
        }




    }


    if(m_video != nullptr && m_video->isVisible())
        m_video->raise();


    CDATA.m_dData[m_sPath.split("/").last()]->m_scaleImage = this->grab();


    return CDATA.m_dData[m_sPath.split("/").last()]->m_scaleImage;
}

void DisplayWidget::setEdit(bool b)
{
    m_bEdit = b;

    if(m_video!=nullptr)
    m_video->setHidden(m_bEdit);


    foreach(ItemBaseContent *t,m_listItem)
    {
        t->setEdit(b);
    }

    if(m_bEdit)
    m_iBorderSize = 2;
    else
        m_iBorderSize = 0;

//{ border: 2px groove gray; border-style: outset;background-color: rgb(220, 220, 220);}

    refreshBg();

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

void DisplayWidget::refreshBg()
{
    LayerData *layerData = CDATA.m_dData[m_layerName] ;

    CDATA.m_bIsEdit = m_bEdit;

    if(layerData!=nullptr)
    ui->wBg->setStyleSheet("QWidget#"+ui->wBg->objectName()+"{"
                                                            "border-image:url("+layerData->m_sBgPath+");"
                          " border: "+QString::number(m_iBorderSize)+"px #6ca5d9; border-style: solid;background-color: rgba(0, 0, 0,0); "
                                                                                                     "}");

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
    qDebug()<<"DisplayWidget:slotUpdate";
    ItemBaseContent *target = dynamic_cast<ItemBaseContent*>(sender());


    emit changeTarget(target->m_sPath);
}

void DisplayWidget::refreshItem()
{
    qDebug()<<"DisplayWidget:refreshItem";

    foreach(ItemBaseContent *item ,m_listItem)
    {
        item->updateItem();
    }


    LayerData *layerData = CDATA.m_dData[m_layerName] ;


    if(layerData==nullptr)
        return ;

  //  ui->wBg->setStyleSheet("QWidget#"+ui->wBg->objectName()+"{border-image:url("+layerData->m_sBgPath+");}");

    refreshBg();


}

void DisplayWidget::raiseItem(QString sPath)
{
    qDebug()<<"DisplayWidget:raiseItem";
    foreach(ItemBaseContent *item ,m_listItem)
    {
        if(item->m_sPath == sPath)
            item->raise();
    }
}

void DisplayWidget::renameItem(QString sOldPath, QString sNewPath)
{
    CDATA.getObj(sOldPath)->m_sWaitRename = sOldPath;

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
    qDebug()<<"DisplayWidget:addItem";
    LayerData *layerData = CDATA.m_dData[m_layerName] ;

    if(layerData == nullptr)
        return;


    ObjData * obj = new ObjData(this);

    QString sTmp = "TEXT_%1";



    if(iIdx == ADD_BASIC_PIC)
    {

        obj->m_sType = E_PIC;

        sTmp = "PIC_%1";

    }

    else if(iIdx == ADD_BASIC_VIDEO)
    {
        obj->m_sType = E_VIDEO;

        sTmp = "VIDEO_%1";

    }

    else if(iIdx == ADD_ADV_BUTTON)
    {
        obj->m_sType = E_BUTTON;

        obj->m_data[Label::txtColor] ="BUTTON";

        sTmp = "BUTTON_%1";

    }

    else if(iIdx == ADD_BASIC_MARQUEE)
    {
        obj->m_sType = E_MARQUEE;

        obj->m_data[Marquee::listText]=QStringList()<<"跑馬燈元件"<<"MARQUEE";

        obj->m_data[Marquee::speed]=3;

       // obj->m_data[Label::bgColor] = QColor(255,255,255,0).name(QColor::HexArgb);

        sTmp = "MARQUEE%1";
    }

    else if(iIdx == ADD_BASIC_QR)
    {
        obj->m_sType = E_QRCODE;

        sTmp = "QRCODE_%1";
    }
    else if(iIdx == ADD_BASIC_TEXT)
    {

            qDebug()<<"TEXT ";
        obj->m_sType = E_TEXT;

        sTmp = "TEXT_%1";

    }

    else if(iIdx == ADD_ADV_TXT)
    {
        obj->m_sType = E_TXVALUE;

        sTmp = "TxValue_%1";

    }
    else
    {
        return ;
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

    obj->m_dDefine = layerData->m_dDefine;

    obj->readData(m_sPath+"/"+sName);

    layerData->m_listData.append(obj);

    ItemBaseContent *item = new ItemBaseContent(ui->wBg);

    connect(item,&ItemBaseContent::sendFocus,this,&DisplayWidget::slotFocus);

    connect(item,&ItemBaseContent::sendUpdate,this,&DisplayWidget::slotUpdate);

    item->setData(layerData->m_listData.last(),m_fDiff);

   // item->m_wBg->setStyleSheet("background-color:green;");

    item->setEdit(true);

    item->show();

    m_listItem.append(item);
}
