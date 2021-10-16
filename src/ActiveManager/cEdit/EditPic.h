#ifndef EDITPIC_H
#define EDITPIC_H

#include <QWidget>
#include <QDebug>
#include "CData.h"
#include "ObjData.h"
#include "DialogSelectFile.h"
#include <QTableWidgetItem>
#include <QShowEvent>

namespace Ui {
class EditPic;
}

class EditPic : public QWidget
{
    Q_OBJECT

public:
    explicit EditPic(QWidget *parent = nullptr);
    ~EditPic();

    void setTarget(ObjData *obj);

    void showEvent(QShowEvent *) override;

private:
    Ui::EditPic *ui;

    ObjData *m_obj =nullptr;


    void readData();

    void refreshTable();
private slots:
    void on_btnSetPic_clicked();

    void on_sbPicSec_valueChanged(int);

};

#endif // EDITPIC_H
