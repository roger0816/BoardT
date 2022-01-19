#include "EditButton.h"
#include "ui_EditButton.h"

EditButton::EditButton(QWidget *parent) :
    EditBase(parent),
    ui(new Ui::EditButton)
{
    ui->setupUi(this);
}

EditButton::~EditButton()
{
    delete ui;
}

void EditButton::setTarget(ObjData *obj)
{
    m_obj = obj;

    m_bLockCallUpdate = true;

    ui->txtText->setText(m_obj->m_data.value(Label::text).toString());

    ui->txtText2->setText(m_obj->m_data.value(Btn::btnText2).toString());

    ui->cbAction->setCurrentIndex(m_obj->m_data.value(Btn::btnType).toInt());

    ui->stackAction->setCurrentIndex(ui->cbAction->currentIndex());

    if(ui->cbAction->currentIndex()==1)
    {
        QString sTarget = m_obj->m_data.value(Btn::btnTypeNote).toString();
        int iIdx = m_listLayerName.indexOf(sTarget);


        qDebug()<<"target : "<<sTarget<<" iId : "<<iIdx;
        if(iIdx<0)
        {
            ui->cbPageSelect->setCurrentIndex(0);
        }
        else
        {
            ui->cbPageSelect->setCurrentIndex(iIdx+1);
        }
      //  ui->cbPageSelect->setCurrentIndex(iIdx);
    }


    getCmdList();

    m_bLockCallUpdate = false;

}

void EditButton::setLayerList(QStringList listName)
{
    m_bLockCallUpdate = true;

    ui->cbPageSelect->clear();

    m_listLayerName = listName;

    listName.push_front("無");

    ui->cbPageSelect->addItems(listName);

    m_bLockCallUpdate = false;

}

QStringList EditButton::getCmdList()
{
    QDir dir(QApplication::applicationDirPath()+"/cmd");

   QStringList list= dir.entryList(QDir::Files | QDir::NoDotAndDotDot);

   ui->cbCmd->clear();

   list.push_front("無");

   ui->cbCmd->addItems(list);


  return list;
}

void EditButton::on_btnSelectFont_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    EditBase::setEditFont(m_obj,Label::font,ui->btnSelectFont);

    emit callUpdate();
}

void EditButton::on_btnTxtColor_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    EditBase::setEditColor(m_obj,Label::txtColor);

    emit callUpdate();
}

void EditButton::on_btnBgColor_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    EditBase::setEditColor(m_obj,Label::bgColor);

    emit callUpdate();
}

void EditButton::on_btnBgImage_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    if(EditBase::setEditBgImage(m_obj,"選擇元件背景圖",Label::imagePath))
        emit callUpdate();
}

void EditButton::on_btnClearBg_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    EditBase::clearEditBgImage(m_obj,Label::imagePath);

    emit callUpdate();
}

void EditButton::on_txtText_textChanged(const QString &arg1)
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_obj->m_data[Label::text] = arg1;

    emit callUpdate();
}

void EditButton::on_txtText2_textChanged(const QString &arg1)
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_obj->m_data[Btn::btnText2] = arg1;

    emit callUpdate();
}

void EditButton::on_cbAction_currentIndexChanged(int index)
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_obj->m_data[Btn::btnType] = index;

    ui->stackAction->setCurrentIndex(index);

    emit callUpdate();
}


void EditButton::on_cbPageSelect_currentIndexChanged(const QString &arg1)
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    QString st = arg1;

    if(ui->cbPageSelect->currentIndex()==0)
    {
        st ="";
    }

    m_obj->m_data[Btn::btnTypeNote] = st;

    emit callUpdate();
}


void EditButton::on_cbCmd_currentTextChanged(const QString &arg1)
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    QString st = arg1;

    if(ui->cbPageSelect->currentIndex()==0)
    {
        st ="";
    }

    m_obj->m_data[Btn::btnTypeNote] = st;

    emit callUpdate();
}
