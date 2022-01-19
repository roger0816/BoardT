#ifndef EDITPIC_H
#define EDITPIC_H

#include <QWidget>
#include "EditBase.h"
#include <QDebug>
#include "CData.h"
#include "ObjData.h"
#include "DialogSelectFile.h"
#include <QTableWidgetItem>
#include <QShowEvent>

namespace Ui {
class EditPic;
}

class EditPic : public EditBase
{
    Q_OBJECT

public:
    explicit EditPic(QWidget *parent = nullptr);
    ~EditPic();

    void setTarget(ObjData *obj) override;

    void showEvent(QShowEvent *) override;

    void clearListView();

private:
    Ui::EditPic *ui;




    void refreshTable();
private slots:
    void on_btnSetPic_clicked();

    void on_sbPicSec_valueChanged(int);

};

#endif // EDITPIC_H
