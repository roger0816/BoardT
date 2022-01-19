#include "EditMar.h"
#include "ui_EditMar.h"

EditMar::EditMar(QWidget *parent) :
    EditBase(parent),
    ui(new Ui::EditMar)
{
    ui->setupUi(this);

    m_listMar<<ui->txtMar0<<ui->txtMar1<<ui->txtMar2<<ui->txtMar3<<ui->txtMar4;
    foreach(QLineEdit *tar,m_listMar)
    {
        connect(tar,&QLineEdit::textChanged,this,&EditMar::slotMarChange);
    }
}

EditMar::~EditMar()
{
    delete ui;
}

void EditMar::setTarget(ObjData *obj)
{
    m_obj = obj;

    readData();
}

void EditMar::readData()
{
    if(m_obj==nullptr)
        return ;

    m_bLockCallUpdate = true;

    QStringList list = m_obj->m_data.value(Marquee::listText).toStringList();

    for(int i=0;i<m_listMar.length() && i <list.length() ;i++)
    {
        m_listMar[i]->setText(list[i]);
    }


    ui->sbMar_2->setValue(m_obj->m_data.value(Marquee::speed).toInt());


    m_bLockCallUpdate = false;

    emit callUpdate();
}

void EditMar::on_btnMarTxColor_2_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    EditBase::setEditColor(m_obj,Label::txtColor);

    emit callUpdate();
}

void EditMar::on_btnMarBgColor_2_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    EditBase::setEditColor(m_obj,Label::bgColor);

    emit callUpdate();
}

void EditMar::on_btnMarFont_2_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    EditBase::setEditFont(m_obj,Label::font,ui->btnMarFont_2);

    emit callUpdate();
}

void EditMar::on_sbMar_2_valueChanged(int arg1)
{
    if(m_obj == nullptr)
        return ;
    m_obj->m_data[Marquee::speed] = ui->sbMar_2->value();

    emit callUpdate();
}

void EditMar::slotMarChange(const QString &)
{



    QStringList list ;

    for(int i=0;i<m_listMar.length();i++)
    {
        QString sText = m_listMar[i]->text();

        if(sText.trimmed()!="")
        {
            list.append(sText);

        }

    }

    m_obj->m_data[Marquee::listText]=list;


    emit callUpdate();
}


