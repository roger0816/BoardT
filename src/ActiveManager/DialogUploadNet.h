#ifndef DIALOGUPLOADNET_H
#define DIALOGUPLOADNET_H

#include <QDialog>
#include <QCheckBox>
#include <QLineEdit>
#include <QSettings>
#include "CData.h"
#include "DialogMsg.h"

namespace Ui {
class DialogUploadNet;
}

struct DataUploadNet
{
    void setData(QStringList listData)
    {
        while(listData.length()<4)
            listData.append("");

        ch->setChecked(listData.at(0).toInt());

        txIp->setText(listData.at(1));

        txId->setText(listData.at(2));

        txPass->setText(listData.at(3));


    }

    QStringList getData()
    {
        QStringList listRe;

        listRe.append(QString::number(ch->isChecked()));

        listRe.append(txIp->text());

        listRe.append(txId->text());

        listRe.append(txPass->text());


        return listRe;
    }


    QCheckBox *ch;

    QLineEdit *txIp;

    QLineEdit *txId;

    QLineEdit *txPass;


};

class DialogUploadNet : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUploadNet(QWidget *parent = nullptr);
    ~DialogUploadNet();

private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

private:
    Ui::DialogUploadNet *ui;

    void read();

    void write();

    void upload (QString sIp, QString sUser,QString sPassword);


    QList<DataUploadNet> m_listData;
};

#endif // DIALOGUPLOADNET_H
