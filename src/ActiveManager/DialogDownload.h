#ifndef DIALOGDOWNLOAD_H
#define DIALOGDOWNLOAD_H

#include <QDialog>

namespace Ui {
class DialogDownload;
}

class DialogDownload : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDownload(QWidget *parent = nullptr);
    ~DialogDownload();

    void setIp(QString sIp);
    QString ip();

    QString id();

    QString pw();



private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

private:
    Ui::DialogDownload *ui;



};

#endif // DIALOGDOWNLOAD_H
