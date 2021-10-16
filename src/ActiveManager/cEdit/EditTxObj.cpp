#include "EditTxObj.h"
#include "ui_EditTxObj.h"

EditTxObj::EditTxObj(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditTxObj)
{
    ui->setupUi(this);
}

EditTxObj::~EditTxObj()
{
    delete ui;
}

void EditTxObj::setTarget(ObjData *obj)
{
    m_obj = obj;

    readData();
}

void EditTxObj::readData()
{

    m_bLockCallUpdate = true;

    QFile file(QApplication::applicationDirPath()+"/input.txt");

    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();

        QString st(data);

        ui->cbTxValue->clear();

        QStringList list ;

        while(list.length()< st.split(",").length())
        {
            list.append(QString::number(list.length()));
        }

        ui->cbTxValue->addItems(list);


    }

    file.close();


    if(m_obj!=nullptr)
    {

        int iIdx = m_obj->m_data[TxtValue::index].toInt();

        if(ui->cbTxValue->count()>0 &&  iIdx < ui->cbTxValue->count())
        ui->cbTxValue->setCurrentIndex(iIdx);

        QStringList listText = m_obj->m_data.value(TxtValue::msg).toStringList();

        while(listText.length()<3)
        {
            listText.append("");
        }

        ui->sbMin->setValue(m_obj->m_data.value(TxtValue::min).toInt());


        ui->sbMax->setValue(m_obj->m_data.value(TxtValue::max).toInt());

        ui->txTxValueMinMsg->setText(listText.first());

        ui->txTxValueMsg->setText(listText.at(1));

        ui->txTxValueMaxMsg->setText(listText.last());


    }


   // ui->chCent2->setChecked(m_obj->m_data.value(Label::alignCenter).toInt());


    m_bLockCallUpdate = false;
}

void EditTxObj::updateTxValue()
{
        if(m_obj ==nullptr || m_bLockCallUpdate )
            return ;


        m_obj->m_data[TxtValue::index] = ui->cbTxValue->currentIndex();


        m_obj->m_data[TxtValue::playSpeed]= ui->sbTxValueDisplay->value();

        m_obj->m_data[TxtValue::readSpeed]= ui->sbTxValueRead->value();

        m_obj->m_data[TxtValue::min] = ui->sbMin->value();

        m_obj->m_data[TxtValue::max] = ui->sbMax->value();


        QStringList listText ;

        listText<<ui->txTxValueMinMsg->text();

        listText<<ui->txTxValueMsg->text();

        listText<<ui->txTxValueMaxMsg->text();

        m_obj->m_data[TxtValue::msg] = listText;


        emit callUpdate();

}

void EditTxObj::on_cbTxValue_currentIndexChanged(int )
{
    updateTxValue();
}

void EditTxObj::on_sbTxValueRead_valueChanged(int)
{
    updateTxValue();
}

void EditTxObj::on_sbTxValueDisplay_valueChanged(int )
{
    updateTxValue();
}

//


void EditTxObj::on_sbMin_valueChanged(double )
{
    updateTxValue();
}

void EditTxObj::on_txTxValueMinMsg_textChanged(const QString &)
{
    updateTxValue();
}




void EditTxObj::on_sbMax_valueChanged(double)
{
    updateTxValue();
}

void EditTxObj::on_txTxValueMaxMsg_textChanged(const QString &)
{
    updateTxValue();
}


void EditTxObj::on_chCentMin_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_func.setCent(m_obj,TxtValue::alignCenterMin,ui->chCentMin);

    emit callUpdate();
}

void EditTxObj::on_chCent_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_func.setCent(m_obj,TxtValue::alignCenter,ui->chCent);

    emit callUpdate();
}

void EditTxObj::on_chCentMax_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_func.setCent(m_obj,TxtValue::alignCenterMax,ui->chCentMax);

    emit callUpdate();
}

void EditTxObj::on_btnSelectFontMin_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_func.setFont(m_obj,TxtValue::fontMin,ui->btnSelectFontMin);

     emit callUpdate();
}

void EditTxObj::on_btnSelectFont_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_func.setFont(m_obj,TxtValue::font,ui->btnSelectFont);

     emit callUpdate();
}

void EditTxObj::on_btnSelectFontMax_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_func.setFont(m_obj,TxtValue::fontMax,ui->btnSelectFontMax);

     emit callUpdate();
}

void EditTxObj::on_btnTxtColorMin_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_func.setColor(m_obj,TxtValue::txtColorMin);

     emit callUpdate();
}

void EditTxObj::on_btnTxtColor_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_func.setColor(m_obj,TxtValue::txtColor);

     emit callUpdate();
}

void EditTxObj::on_btnTxtColorMax_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_func.setColor(m_obj,TxtValue::txtColorMax);

     emit callUpdate();
}

void EditTxObj::on_btnBgColorMin_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_func.setColor(m_obj,TxtValue::bgColorMin);

     emit callUpdate();
}

void EditTxObj::on_btnBgColor_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_func.setColor(m_obj,TxtValue::bgColor);

     emit callUpdate();
}

void EditTxObj::on_btnBgColorMax_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_func.setColor(m_obj,TxtValue::bgColorMax);

     emit callUpdate();
}

void EditTxObj::on_btnBgImageMin_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_func.setBgImage(m_obj,"選擇元件背景圖",TxtValue::imagePathMin);

    emit callUpdate();
}

void EditTxObj::on_btnBgImage_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_func.setBgImage(m_obj,"選擇元件背景圖",TxtValue::imagePath);

    emit callUpdate();
}

void EditTxObj::on_btnBgImageMax_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_func.setBgImage(m_obj,"選擇元件背景圖",TxtValue::imagePathMax);

    emit callUpdate();
}

void EditTxObj::on_btnClearBgMin_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_func.clearBgImage(m_obj,TxtValue::imagePathMin);

    emit callUpdate();
}

void EditTxObj::on_btnClearBg_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_func.clearBgImage(m_obj,TxtValue::imagePath);

    emit callUpdate();
}

void EditTxObj::on_btnClearBgMax_clicked()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_func.clearBgImage(m_obj,TxtValue::imagePathMax);

    emit callUpdate();
}

void EditTxObj::on_sbGpioMin_valueChanged(int arg1)
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_obj->m_data[TxtValue::gpioPinMin]=arg1;

    emit callUpdate();
}

void EditTxObj::on_spGpioValueMin_currentIndexChanged(int index)
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_obj->m_data[TxtValue::gpioValueMin]=index;

    emit callUpdate();
}

void EditTxObj::on_spGpio_valueChanged(int arg1)
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_obj->m_data[TxtValue::gpioPin]=arg1;

    emit callUpdate();
}

void EditTxObj::on_spGpioValue_currentIndexChanged(int index)
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_obj->m_data[TxtValue::gpioValue]=index;

    emit callUpdate();
}

void EditTxObj::on_spGpioMax_valueChanged(int arg1)
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_obj->m_data[TxtValue::gpioPinMax]=arg1;

    emit callUpdate();
}

void EditTxObj::on_spGpioValueMax_currentIndexChanged(int index)
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_obj->m_data[TxtValue::gpioValueMax]=index;

    emit callUpdate();
}

void EditTxObj::on_tabWidget_currentChanged(int index)
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_obj->m_dEditData["EditStatus"] = index;

    emit callUpdate();
}

