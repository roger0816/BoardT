#include "EditLabel.h"
#include "ui_EditLabel.h"

EditLabel::EditLabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditLabel)
{
    ui->setupUi(this);
}

EditLabel::~EditLabel()
{
    delete ui;
}

void EditLabel::setTarget(ObjData *obj)
{
    m_obj = obj;

    readData();
}

void EditLabel::readData()
{
    if(m_obj==nullptr)
        return ;

    m_bLockCallUpdate = true;

    ui->txtText->setText(m_obj->m_data.value(Label::text).toString());

    ui->chCent->setChecked(m_obj->m_data.value(Label::alignCenter).toInt());

    m_bLockCallUpdate = false;

}




void EditLabel::on_btnBgColor_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    func.setColor(m_obj,Label::bgColor);

     emit callUpdate();
}

void EditLabel::on_btnTxtColor_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    func.setColor(m_obj,Label::txtColor);

     emit callUpdate();
}

void EditLabel::on_btnBgImage_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    func.setBgImage(m_obj,"選擇元件背景圖",Label::imagePath);

    emit callUpdate();
}

void EditLabel::on_btnClearBg_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    func.clearBgImage(m_obj,Label::imagePath);

    emit callUpdate();
}

void EditLabel::on_btnSelectFont_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    func.setFont(m_obj,Label::font,ui->btnSelectFont);

     emit callUpdate();
}

void EditLabel::on_chCent_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    func.setCent(m_obj,Label::alignCenter,ui->chCent);

    emit callUpdate();
}

void EditLabel::on_txtText_textChanged(const QString &)
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_obj->m_data[Label::text] = ui->txtText->text();

    emit callUpdate();
}
