#include "ItemEditText.h"
#include "ui_ItemEditText.h"

ItemEditText::ItemEditText(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemEditText)
{
    ui->setupUi(this);
}

ItemEditText::~ItemEditText()
{
    delete ui;
}

void ItemEditText::init()
{
    ui->txtText->setText("TEXT");

    ui->chCent->setChecked(true);

    ui->spSize->setValue(22);

    ui->spBgR->setValue(255);
    ui->spBgG->setValue(255);
    ui->spBgB->setValue(255);
    ui->spBgA->setValue(255);

    ui->spTextR->setValue(0);
    ui->spTextR->setValue(0);
    ui->spTextR->setValue(0);
    ui->spTextA->setValue(255);

    ui->txtBgImage->clear();

    ui->txtCmd->clear();

    syncData();
}

void ItemEditText::setData(DataText data)
{
    m_data = data;

    m_bOnlySet = true;

    ui->txtText->setText(m_data.sText);

    ui->spSize->setValue(m_data.iPixSize);

    ui->chCent->setChecked(m_data.bIsCent);

    ui->spTextR->setValue(m_data.textColor.red());

    ui->spTextG->setValue(m_data.textColor.green());

    ui->spTextB->setValue(m_data.textColor.blue());

    ui->spTextA->setValue(m_data.textColor.alpha());

    ui->spBgR->setValue(m_data.bgColor.red());

    ui->spBgG->setValue(m_data.bgColor.green());

    ui->spBgB->setValue(m_data.bgColor.blue());

    ui->spBgA->setValue(m_data.bgColor.alpha());

    ui->txtBgImage->setText(m_data.m_sImagePath);

    ui->txtCmd->setText(m_data.m_sCmdPath);

    m_bOnlySet =false;


}

void ItemEditText::syncData()
{
    m_data.sText = ui->txtText->text().trimmed();

    m_data.iPixSize = ui->spSize->value();

    m_data.bIsCent = ui->chCent->isChecked();

    m_data.textColor = QColor(qRgba(ui->spTextR->value(),ui->spTextG->value(),
                                    ui->spTextB->value(),ui->spTextA->value()));

    m_data.bgColor = QColor(qRgba(ui->spBgR->value(),ui->spBgG->value(),
                                  ui->spBgB->value(),ui->spBgA->value()));


    m_data.m_sImagePath = ui->txtBgImage->text();

    m_data.m_sCmdPath = ui->txtCmd->text();

}


void ItemEditText::on_txtText_textEdited(const QString &arg1)
{
    Q_UNUSED(arg1);

    if(m_bOnlySet)
        return;
    syncData();

    emit updateData();
}


void ItemEditText::on_spSize_valueChanged(int arg1)
{
    Q_UNUSED(arg1);

    if(m_bOnlySet)
        return;
    syncData();

    emit updateData();
}

void ItemEditText::on_chCent_stateChanged(int arg1)
{
    Q_UNUSED(arg1);

    if(m_bOnlySet)
        return;
    syncData();

    emit updateData();
}

void ItemEditText::on_spTextR_valueChanged(int arg1)
{
    Q_UNUSED(arg1);

    if(m_bOnlySet)
        return;
    syncData();

    emit updateData();
}

void ItemEditText::on_spTextG_valueChanged(int arg1)
{
    Q_UNUSED(arg1);

    if(m_bOnlySet)
        return;
    syncData();

    emit updateData();
}

void ItemEditText::on_spTextB_valueChanged(int arg1)
{
    Q_UNUSED(arg1);

    if(m_bOnlySet)
        return;
    syncData();

    emit updateData();
}

void ItemEditText::on_spTextA_valueChanged(int arg1)
{
    Q_UNUSED(arg1);

    if(m_bOnlySet)
        return;
    syncData();

    emit updateData();
}

void ItemEditText::on_spBgR_valueChanged(int arg1)
{
    Q_UNUSED(arg1);

    if(m_bOnlySet)
        return;
    syncData();

    emit updateData();
}

void ItemEditText::on_spBgG_valueChanged(int arg1)
{
    Q_UNUSED(arg1);

    if(m_bOnlySet)
        return;
    syncData();

    emit updateData();
}

void ItemEditText::on_spBgB_valueChanged(int arg1)
{
    Q_UNUSED(arg1);

    if(m_bOnlySet)
        return;
    syncData();

    emit updateData();
}

void ItemEditText::on_spBgA_valueChanged(int arg1)
{
    Q_UNUSED(arg1);

    if(m_bOnlySet)
        return;
    syncData();

    emit updateData();
}

void ItemEditText::on_txtBgImage_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

    if(m_bOnlySet)
        return;
    syncData();

    emit updateData();
}

void ItemEditText::on_txtCmd_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

    if(m_bOnlySet)
        return;
    syncData();

    emit updateData();
}

void ItemEditText::on_btnBgImage_clicked()
{
    QString sPath = QFileDialog::getOpenFileName(this,"選擇元件背景圖",QApplication::applicationDirPath(),"*.png");

    ui->txtBgImage->setText(sPath);

    syncData();

    emit updateData();

}
