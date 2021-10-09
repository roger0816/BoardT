#ifndef DIALOGUPLOADUSB_H
#define DIALOGUPLOADUSB_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class DialogUploadUsb;
}

class DialogUploadUsb : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUploadUsb(QWidget *parent = nullptr);
    ~DialogUploadUsb();

    QString m_sPath;

private slots:
    void on_btnSelect_clicked();

private:
    Ui::DialogUploadUsb *ui;
};

#endif // DIALOGUPLOADUSB_H
