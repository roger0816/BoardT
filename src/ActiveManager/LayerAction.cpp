#include "LayerAction.h"
#include "ui_LayerAction.h"

LayerAction::LayerAction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerAction)
{
    ui->setupUi(this);


    m_listKeyMapping<<CMD_None<<CMD_Page<<CMD_PageNoStop<<CMD_Pop
                   <<CMD_Change<<CMD_Gpio<<CMD_Script;

//    m_buttonRb.addButton(ui->rbNone,_NONE);

//    m_buttonRb.addButton(ui->rbPage,_PAGE);

//    m_buttonRb.addButton(ui->rbPageNoStop,_PAGE_NO_STOP);

//    m_buttonRb.addButton(ui->rbPop,_POP);

//    m_buttonRb.addButton(ui->rbChange,_CHANGE);

//    m_buttonRb.addButton(ui->rbGpio,_GPIO);

//    m_buttonRb.addButton(ui->rbCmd,_SCRIPT);

//    connect(&m_buttonRb,&QButtonGroup::idPressed,this,&LayerAction::slotRbClicked);


    m_listBtn.append(ui->rbNone);
    m_listBtn.append(ui->rbPage);
    m_listBtn.append(ui->rbPageNoStop);
    m_listBtn.append(ui->rbPop);
    m_listBtn.append(ui->rbChange);
    m_listBtn.append(ui->rbGpio);
    m_listBtn.append(ui->rbCmd);

    foreach (QRadioButton *btn, m_listBtn)
    {
        connect(btn,&QRadioButton::clicked,this,&LayerAction::slotClicked);
    }





    emit slotRbClicked(_NONE);


    ui->groupBox->hide();


}

LayerAction::~LayerAction()
{
    delete ui;
}

void LayerAction::setTarget(QString sObjPath)
{

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

    m_sObjPath = sObjPath;

    qDebug()<<m_obj->m_sName;

    qDebug()<<m_obj->m_dataCmd.sCmd<<" , "<<m_obj->m_dataCmd.sValue1<<" , "<<m_obj->m_dataCmd.sValue2;


    refresh();

}


void LayerAction::refresh()
{
    if(m_obj == nullptr)
        return ;

    m_bLockSend = true;

    QString sCmd = m_obj->m_dataCmd.sCmd;

    int iIdx = _NONE;

    if(sCmd == CMD_Page)
        iIdx = _PAGE;
    else if(sCmd == CMD_PageNoStop)
        iIdx = _PAGE_NO_STOP;

    else if(sCmd == CMD_Pop)
        iIdx = _POP;

    else if(sCmd == CMD_Change)
        iIdx = _CHANGE;
    else if(sCmd == CMD_Gpio)
        iIdx = _GPIO;
    else if(sCmd == CMD_Script)
        iIdx = _SCRIPT;


    m_iCurrentIdx = iIdx;

    qDebug()<<"read idx : "<<iIdx;



    QStringList listCbKey = CDATA.m_dData.keys();


    ui->cbLayer->clear();



    ui->cbLayer->addItems(listCbKey);



    ui->cbChangeLayer->clear();

    ui->cbChangeLayer->addItems(listCbKey);

    if( listCbKey.indexOf(m_obj->m_dataCmd.sValue1) >=0 )
    {
        ui->cbLayer->setCurrentText(m_obj->m_dataCmd.sValue1);

        ui->cbChangeLayer->setCurrentText(m_obj->m_dataCmd.sValue1);
    }


    ui->cbChangeObj->clear();


    QStringList listObjKey;


    if(CDATA.m_dData[m_sLayerName]!=nullptr &&
            CDATA.m_dData[m_sLayerName]->m_listData.length()>0)
    {

        QList<ObjData*> list = CDATA.m_dData[m_sLayerName]->m_listData;


        for(int i=0;i<list.length();i++)
        {
            listObjKey.append(list[i]->m_sName);
        }


        ui->cbChangeObj->addItems(listObjKey);
    }


    if( listObjKey.indexOf(m_obj->m_dataCmd.sValue2) >=0 )
    {
        ui->cbChangeObj->setCurrentText(m_obj->m_dataCmd.sValue2);


    }


   // m_buttonRb.button(iIdx)->setChecked(true);

    slotRbClicked(iIdx);

    ui->groupBox->show();

    m_bLockSend = false;


}

void LayerAction::writeData()
{
    if(m_bLockSend)
        return ;

    ObjData *objData =  CDATA.getObj(m_sObjPath);

    if(objData == nullptr)
        return ;

    DataCmd data;


    data.sCmd = m_listKeyMapping.at(qBound(0,m_iCurrentIdx,m_listKeyMapping.length()-1));


    if(m_iCurrentIdx ==_NONE)
    {
        data.sCmd="";
    }
    else if (m_iCurrentIdx ==_PAGE)
    {
        data.sValue1 = ui->cbLayer->currentText();

        data.sValue2 = "1";
    }
    else if (m_iCurrentIdx ==_PAGE_NO_STOP)
    {
        data.sValue1 = ui->cbLayer->currentText();

        data.sValue2 = "0";
    }
    else if (m_iCurrentIdx ==_CHANGE)
    {

    }
    else if (m_iCurrentIdx ==_GPIO)
    {
        data.sValue1 = QString::number(ui->sbGpioPin->value());

        data.sValue2 = QString::number(ui->sbGpioValue->value());
    }
    else if (m_iCurrentIdx ==_SCRIPT)
    {
        data.sValue1 = ui->txScript->text();
    }

    qDebug()<<"write cmd : "<<data.sCmd<<", "<<data.sValue1<<" , "<<data.sValue2;

    objData->m_dataCmd = data;
}

void LayerAction::slotClicked()
{
   slotRbClicked(m_listBtn.indexOf(dynamic_cast<QRadioButton*>(sender())));
}

void LayerAction::slotRbClicked(int iId)
{
    ui->stackedWidget->setCurrentIndex(iId);

    if(iId ==_PAGE || iId == _PAGE_NO_STOP)
        ui->stackedWidget->setCurrentWidget(ui->pageLayer);


    m_iCurrentIdx = iId;

    qDebug()<<"clicked id : "<<iId;

    writeData();
}

void LayerAction::on_cbChangeLayer_currentIndexChanged(int index)
{
    writeData();
}

void LayerAction::on_cbChangeObj_currentIndexChanged(int index)
{
    writeData();
}

void LayerAction::on_txScript_textEdited(const QString &arg1)
{
    writeData();
}

void LayerAction::on_sbGpioPin_valueChanged(int arg1)
{
    writeData();
}

void LayerAction::on_sbGpioValue_valueChanged(int arg1)
{
    writeData();
}

void LayerAction::on_cbLayer_currentIndexChanged(int index)
{
    writeData();
}
