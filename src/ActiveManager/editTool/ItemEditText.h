#ifndef ITEMEDITTEXT_H
#define ITEMEDITTEXT_H

#include <QWidget>
#include <QFileDialog>
#include <QDebug>
#include "CData.h"


namespace Ui {
class ItemEditText;
}

class ItemEditText : public QWidget
{
    Q_OBJECT

public:
    explicit ItemEditText(QWidget *parent = nullptr);
    ~ItemEditText();

    void init();

    void setData(DataText data);

    DataText getData(){return m_data;}


private slots:
    void on_txtText_textEdited(const QString &arg1);


    void on_spSize_valueChanged(int arg1);

    void on_chCent_stateChanged(int arg1);

    void on_spTextR_valueChanged(int arg1);
    void on_spTextG_valueChanged(int arg1);
    void on_spTextB_valueChanged(int arg1);
    void on_spTextA_valueChanged(int arg1);


    void on_spBgR_valueChanged(int arg1);
    void on_spBgG_valueChanged(int arg1);
    void on_spBgB_valueChanged(int arg1);
    void on_spBgA_valueChanged(int arg1);

    void on_txtBgImage_textChanged(const QString &arg1);

    void on_txtCmd_textChanged(const QString &arg1);

    void on_btnBgImage_clicked();

signals:
    void updateData();
private:
    Ui::ItemEditText *ui;

    DataText m_data;

    void syncData();

    bool m_bOnlySet = false;
};

#endif // ITEMEDITTEXT_H
