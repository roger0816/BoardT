#ifndef EDITLABEL_H
#define EDITLABEL_H

#include <QWidget>
#include <QDebug>
#include <QFileDialog>
#include <QFontDialog>
#include "ObjData.h"
#include "EditBase.h"
namespace Ui {
class EditLabel;
}

class EditLabel : public EditBase
{
    Q_OBJECT

public:
    explicit EditLabel(QWidget *parent = nullptr);
    ~EditLabel();

    void setTarget(ObjData *obj) override;

private:

    void readData();

private slots:
    void on_btnBgColor_clicked();

    void on_btnTxtColor_clicked();

    void on_btnBgImage_clicked();

    void on_btnClearBg_clicked();

    void on_btnSelectFont_clicked();

    void on_chCent_clicked();

    void on_txtText_textChanged(const QString &);

private:
    Ui::EditLabel *ui;
};

#endif // EDITLABEL_H
