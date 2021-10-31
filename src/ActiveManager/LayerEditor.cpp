#include "LayerEditor.h"
#include "ui_LayerEditor.h"

LayerEditor::LayerEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerEditor)
{
    ui->setupUi(this);

    ui->stackType->setCurrentWidget(ui->pageText);




    connect(ui->pageText,&EditLabel::callUpdate,this,&LayerEditor::callUpdate);

    connect(ui->pageBtn,&EditButton::callUpdate,this,&LayerEditor::callUpdate);


    connect(ui->pageTxValue,&EditTxObj::callUpdate,this,&LayerEditor::callUpdate);

    connect(ui->pageMar,&EditMar::callUpdate,this,&LayerEditor::callUpdate);

    connect(ui->pageDate,&EditDateTime::callUpdate,this,&LayerEditor::callUpdate);

    connect(ui->pageGrid,&EditGrid::callUpdate,this,&LayerEditor::callUpdate);

}

LayerEditor::~LayerEditor()
{
    delete ui;
}

void LayerEditor::setTarget(QString sObjPath)
{
    qDebug()<<"change focus : "<<sObjPath;

    QStringList listTmp = sObjPath.split("/");



    if(listTmp.length()<2)
        return;

    bool bOk = false;

    m_sLayerName = listTmp.at(listTmp.length()-2);

    m_sObjName = listTmp.at(listTmp.length()-1);

    ObjData *data = CDATA.getObj(m_sLayerName,m_sObjName,bOk);

    if(!bOk)
        return;

    m_obj = data;

    m_sPath = sObjPath;


    refresh();



}

void LayerEditor::refresh()
{



    if(m_obj == nullptr)
        return;


    qDebug()<<"refresh ";


    m_bLockCallUpdate = true;

    ui->txtName->setText(m_obj->m_sName);

    ui->sbX->setValue(m_obj->m_rect.x());

    ui->sbY->setValue(m_obj->m_rect.y());

    ui->sbW->setValue(m_obj->m_rect.width());

    ui->sbH->setValue(m_obj->m_rect.height());




    if(m_obj->m_sType == E_TEXT)
    {
        ui->stackType->setCurrentWidget(ui->pageText);

        ui->pageText->setTarget(m_obj);

    }
    else if(m_obj->m_sType == E_PIC)
    {

        ui->pagePic->setTarget(m_obj);

        ui->stackType->setCurrentWidget(ui->pagePic);

    }
    if(m_obj->m_sType == E_BUTTON)
    {
        ui->stackType->setCurrentWidget(ui->pageBtn);

        ui->pageBtn->setLayerList(CDATA.m_dData.keys());

        ui->pageBtn->setTarget(m_obj);


    }

    else if(m_obj->m_sType == E_VIDEO)
    {

        ui->pageVideo->setTarget(m_obj);

        ui->stackType->setCurrentWidget(ui->pageVideo);

    }

    else if(m_obj->m_sType == E_URL)
    {


        ui->stackType->setCurrentWidget(ui->pageUrl);

    }

    else if(m_obj->m_sType == E_DATETIME)
    {

        ui->pageDate->setTarget(m_obj);

        ui->stackType->setCurrentWidget(ui->pageDate);

    }

    else if(m_obj->m_sType == E_MARQUEE)
    {
        ui->stackType->setCurrentWidget(ui->pageMar);

        ui->pageMar->setTarget(m_obj);
        //        QStringList list = m_obj->m_data.value(Marquee::listText).toStringList();

        //        for(int i=0;i<m_listMar.length() && i <list.length() ;i++)
        //        {
        //            m_listMar[i]->setText(list[i]);
        //        }


        //         ui->sbMar->setValue(m_obj->m_data.value(Marquee::speed).toInt());



        //        emit callUpdate();
    }

    else if(m_obj->m_sType == E_QRCODE)
    {
        ui->stackType->setCurrentWidget(ui->pageQr);

        ui->txQr->setText(m_obj->m_data.value(Label::text).toString());

    }

    else if(m_obj->m_sType == E_TXVALUE)
    {
        ui->stackType->setCurrentWidget(ui->pageTxValue);

        ui->pageTxValue->setTarget(m_obj);

    }

    else if(m_obj->m_sType == E_GRID)
    {
        ui->stackType->setCurrentWidget(ui->pageGrid);


        ui->pageGrid->setTarget(m_obj);



    }

    m_bLockCallUpdate =false;
}


void LayerEditor::on_sbX_valueChanged(int)
{
    updateRect();
}


void LayerEditor::on_sbY_valueChanged(int )
{
    updateRect();
}

void LayerEditor::on_sbW_valueChanged(int )
{
    updateRect();
}

void LayerEditor::on_sbH_valueChanged(int )
{
    updateRect();
}


void LayerEditor::updateRect()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_obj->m_rect.setX(ui->sbX->value());

    m_obj->m_rect.setY(ui->sbY->value());

    m_obj->m_rect.setWidth(ui->sbW->value());

    m_obj->m_rect.setHeight(ui->sbH->value());

    emit callUpdate();
}

bool LayerEditor::deleteDirectory(const QString &path)
{
    if (path.isEmpty())
        return false;

    QDir dir(path);
    if(!dir.exists())
        return true;

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList)
    {
        if (fi.isFile())
            fi.dir().remove(fi.fileName());
        else
            deleteDirectory(fi.absoluteFilePath());
    }
    return dir.rmpath(dir.absolutePath());
}



void LayerEditor::on_btnToTop_clicked()
{

 CDATA.m_dData[CDATA.m_sCurrentLayerName]->raise(m_sObjName);

 qDebug()<<"after delete raise : "<<CDATA.m_dData[CDATA.m_sCurrentLayerName]->m_dataLayer.listObjSort;


 emit callRaise(m_sPath);
}

void LayerEditor::on_btnRename_clicked()
{



    if(m_obj == nullptr)
    {
        return ;
    }


    if(m_sPath.split("/").last().trimmed() == ui->txtName->text())
        return ;




    QString sOldPath = m_sPath;

    QStringList listTmp = m_sPath.split("/");

    listTmp.pop_back();

    listTmp.push_back(ui->txtName->text());

    QString sNewPath = listTmp.join("/");

    m_obj->m_sName = listTmp.last();

    qDebug()<<"m_obj name : "<<m_obj->m_sName;

    m_obj->m_sObjPath = sNewPath;

    m_sPath = sNewPath;

    m_sObjName = m_obj->m_sName;


    QVariantList *listSort = &CDATA.m_dData[CDATA.m_sCurrentLayerName]->m_dataLayer.listObjSort;

    int iIdx =  listSort->indexOf(sOldPath.split("/").last());

    if(iIdx>=0 && iIdx < listSort->length())
    {
        listSort->replace(iIdx,sNewPath.split("/").last());
    }

    QDir().rename(sOldPath,sNewPath);


    emit callRename(sOldPath,sNewPath);
    // callUpdate();

    qDebug()<<"after rename sort : "<<CDATA.m_dData[CDATA.m_sCurrentLayerName]->m_dataLayer.listObjSort;


}




void LayerEditor::on_btnDelete_clicked()
{
    DialogMsg msg;

    msg.setDialogInfo("確定要刪除此元件嗎？",QStringList()<<"否"<<"是");

    int iRe = msg.exec();

    if(iRe==1)
    {


        QVariantList *listSort = &CDATA.m_dData[CDATA.m_sCurrentLayerName]->m_dataLayer.listObjSort;

        listSort->removeOne(m_sObjName);

        deleteDirectory(m_sPath);

        emit callDelete(m_sPath);

        qDebug()<<"after delete sort : "<<CDATA.m_dData[CDATA.m_sCurrentLayerName]->m_dataLayer.listObjSort;

    }

    if(ui->stackType->currentWidget() == ui->pagePic)
        ui->pagePic->clearListView();


}







void LayerEditor::on_txQr_textChanged(const QString &arg1)
{
    m_obj->m_data[Label::text]= ui->txQr->text();

    emit callUpdate();
}





void LayerEditor::on_txUrl_textChanged(const QString &arg1)
{
    if(m_obj==nullptr)
        return;
    m_obj->m_data[Url::source]= arg1;

}
