#include "EditDateTime.h"
#include "ui_EditDateTime.h"

EditDateTime::EditDateTime(QWidget *parent) :
    EditBase(parent),
    ui(new Ui::EditDateTime)
{
    ui->setupUi(this);
}

EditDateTime::~EditDateTime()
{
    delete ui;
}

void EditDateTime::setTarget(ObjData *obj)
{
    m_obj = obj;

    m_bLockCallUpdate = true;

    ui->sbSec->setValue(m_obj->m_data[DateTime::speed].toInt());

    ui->cbDate->setCurrentText( m_obj->m_data[DateTime::dateStr].toString());

    ui->cbTime->setCurrentText(m_obj->m_data[DateTime::timeStr].toString());

    m_bLockCallUpdate = false;


}

void EditDateTime::on_cbDate_currentIndexChanged(const QString &)
{

    QString sDate = ui->cbDate->currentText();

    sDate = sDate.replace("年","yyyy").replace("月","MM").replace("日","dd").replace("星期幾","ddd");

    ui->txDate->setText(sDate);

}


void EditDateTime::on_cbTime_currentIndexChanged(const QString &)
{
    QString sTime = ui->cbTime->currentText();

    sTime = sTime.replace("時","hh").replace("分","mm").replace("秒","ss");

    ui->txTime->setText(sTime);
}


void EditDateTime::on_sbSec_valueChanged(int )
{

    setSetting();
}

void EditDateTime::setSetting()
{
    if(m_obj==nullptr || m_bLockCallUpdate)
        return;



    m_obj->m_data[DateTime::dateStr] = ui->txDate->text();


    m_obj->m_data[DateTime::timeStr] = ui->txTime->text();

    m_obj->m_data[DateTime::speed] = ui->sbSec->value();

    emit callUpdate();
}


void EditDateTime::on_txDate_textChanged(const QString &)
{
        setSetting();
}


void EditDateTime::on_txTime_textChanged(const QString &)
{
        setSetting();
}


void EditDateTime::on_btnColor_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    EditBase::setEditColor(m_obj,Label::txtColor);

     emit callUpdate();
}


void EditDateTime::on_btnBg_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

     EditBase::setEditColor(m_obj,Label::bgColor);

     emit callUpdate();
}


void EditDateTime::on_btnFont_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    EditBase::setEditFont(m_obj,Label::font,ui->btnFont);

     emit callUpdate();
}

