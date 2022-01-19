#ifndef EDITDATETIME_H
#define EDITDATETIME_H

#include <QWidget>
#include "EditBase.h"
namespace Ui {
class EditDateTime;
}

class EditDateTime : public EditBase
{
    Q_OBJECT

public:
    explicit EditDateTime(QWidget *parent = nullptr);
    ~EditDateTime();

     void setTarget(ObjData *obj) override;

private slots:
     void on_cbDate_currentIndexChanged(const QString &);

     void on_cbTime_currentIndexChanged(const QString &);

     void on_sbSec_valueChanged(int);

     void on_txDate_textChanged(const QString &);

     void on_txTime_textChanged(const QString &);

     void on_btnColor_clicked();

     void on_btnBg_clicked();

     void on_btnFont_clicked();

private:
    Ui::EditDateTime *ui;

    void setSetting();
};

#endif // EDITDATETIME_H
