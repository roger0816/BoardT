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

QPixmap DisplayWidget::setLayer(QString m_sPath)
{
    qDebug()<<"layer path : "<<m_sPath;
    LayerData *layerData = CDATA.m_dData[m_sPath.split("/").last()] ;

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
//        item->raise();
    }
}
