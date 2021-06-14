#ifndef EDITTXOBJ_H
#define EDITTXOBJ_H

#include <QWidget>
#include "EditFunc.h"
#include "ObjData.h"

namespace Ui {
class EditTxObj;
}

class EditTxObj : public QWidget
{
    Q_OBJECT

public:
    explicit EditTxObj(QWidget *parent = nullptr);
    ~EditTxObj();

    void setTarget(ObjData *obj);


private:
    void updateTxValue();

    void readData();

    ObjData *m_obj =nullptr;

    bool m_bLockCallUpdate = false;

    EditFunc m_func;

signals:
    void callUpdate();

private slots:
    void on_cbTxValue_currentIndexChanged(int);

    void on_sbTxValueRead_valueChanged(int );

    void on_sbTxValueDisplay_valueChanged(int);


    void on_sbMin_valueChanged(double);

    void on_txTxValueMinMsg_textChanged(const QString &);

    void on_sbMax_valueChanged(double );

    void on_txTxValueMaxMsg_textChanged(const QString &);


    void on_chCentMin_clicked();

    void on_chCent_clicked();

    void on_chCentMax_clicked();

    void on_btnSelectFontMin_clicked();

    void on_btnSelectFont_clicked();

    void on_btnSelectFontMax_clicked();

    void on_btnTxtColorMin_clicked();

    void on_btnTxtColor_clicked();

    void on_btnTxtColorMax_clicked();

    void on_btnBgColorMin_clicked();

    void on_btnBgColor_clicked();

    void on_btnBgColorMax_clicked();

    void on_btnBgImageMin_clicked();

    void on_btnBgImage_clicked();

    void on_btnBgImageMax_clicked();

    void on_btnClearBgMin_clicked();

    void on_btnClearBg_clicked();

    void on_btnClearBgMax_clicked();

    void on_sbGpioMin_valueChanged(int arg1);

    void on_spGpioValueMin_currentIndexChanged(int index);

    void on_spGpio_valueChanged(int arg1);

    void on_spGpioValue_currentIndexChanged(int index);

    void on_spGpioMax_valueChanged(int arg1);

    void on_spGpioValueMax_currentIndexChanged(int index);

private:
    Ui::EditTxObj *ui;
};

#endif // EDITTXOBJ_H
