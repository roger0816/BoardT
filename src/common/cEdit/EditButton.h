#ifndef EDITBUTTON_H
#define EDITBUTTON_H

#include <QWidget>
#include "EditBase.h"

namespace Ui {
class EditButton;
}

class EditButton : public EditBase
{
    Q_OBJECT

public:
    explicit EditButton(QWidget *parent = nullptr);
    ~EditButton();

    void setTarget(ObjData *obj) override;

    void setLayerList(QStringList listName);

private:

    QStringList m_listLayerName;

    QStringList getCmdList();
private slots:
    void on_btnSelectFont_clicked();

    void on_btnTxtColor_clicked();

    void on_btnBgColor_clicked();

    void on_btnBgImage_clicked();

    void on_btnClearBg_clicked();

    void on_txtText_textChanged(const QString &arg1);

    void on_txtText2_textChanged(const QString &arg1);

    void on_cbAction_currentIndexChanged(int index);

    void on_cbPageSelect_currentIndexChanged(const QString &arg1);



    void on_cbCmd_currentTextChanged(const QString &arg1);

private:
    Ui::EditButton *ui;
};

#endif // EDITBUTTON_H
