#ifndef DIALOGPICDETAIL_H
#define DIALOGPICDETAIL_H

#include <QDialog>
#include <QResizeEvent>
#include <QShowEvent>

namespace Ui {
class DialogPicDetail;
}

class DialogPicDetail : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPicDetail(QWidget *parent = nullptr);
    ~DialogPicDetail();

    void setPicPath(QString sPathFile);

private:
    Ui::DialogPicDetail *ui;


    void resizeEvent(QResizeEvent * ) override;

    void showEvent(QShowEvent * ) override;

    QString m_sFilePath="";
};

#endif // DIALOGPICDETAIL_H
