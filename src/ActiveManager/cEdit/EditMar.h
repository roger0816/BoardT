#ifndef EDITMAR_H
#define EDITMAR_H

#include <QWidget>
#include "EditBase.h"
#include <QLineEdit>
namespace Ui {
class EditMar;
}

class EditMar : public EditBase
{
    Q_OBJECT

public:
    explicit EditMar(QWidget *parent = nullptr);
    ~EditMar();

    void setTarget(ObjData *obj) override;

private:


    void readData();

    QList<QLineEdit*> m_listMar;




private slots:
    void on_btnMarTxColor_2_clicked();

    void on_btnMarBgColor_2_clicked();

    void on_btnMarFont_2_clicked();

    void on_sbMar_2_valueChanged(int arg1);

    void slotMarChange(const QString &);
private:
    Ui::EditMar *ui;
};

#endif // EDITMAR_H
