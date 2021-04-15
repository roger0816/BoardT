#ifndef DIALOGPOP_H
#define DIALOGPOP_H

#include <QWidget>
#include <QPushButton>
#include "qrencode.h"
#include <QPainter>
#include <QDebug>

namespace Ui {
class DialogPop;
}


class WidgetBg :public QWidget
{
    Q_OBJECT

public:
    explicit WidgetBg(QWidget *parent = nullptr):QWidget(parent){}

    void mousePressEvent(QMouseEvent *) override;
signals:
    void clicked();

};

class DialogPop : public QWidget
{
    Q_OBJECT

public:
    explicit DialogPop(QWidget *parent = nullptr);
    ~DialogPop();

    void setPicRun(QStringList listPath,QRect rect);

    void setActionRun(QStringList listPath,QStringList listUrl,QRect rect);


    QList<QPushButton*> m_listBtn;

    void setQrCode(QString sText, QRect rect);

    void setBg(QString sFilePath);
signals:
    void sendTouchLock();

private slots:
    void on_btnBack_clicked();

    void btnClicked();

private:
    Ui::DialogPop *ui;

    QStringList m_listPicPath;

    QStringList m_listUrl;

    QPixmap drawImageQr(QRcode *code);

    void displayInfo();
};

#endif // DIALOGPOP_H
