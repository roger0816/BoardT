#ifndef DIALOGMSG_H
#define DIALOGMSG_H

#include <QDialog>

namespace Ui {
class DialogMsg;
}

class DialogMsg : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMsg(QWidget *parent = nullptr);
    ~DialogMsg();

    void setDialogInfo(QString sMsg,QStringList listBtnText);

    void setInput(QString sTitle, QString sPreInplut, QStringList listBtnName);

    void setButton(QStringList listName);

    QString getInput();

private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

private:
    Ui::DialogMsg *ui;
};

#endif // DIALOGMSG_H
