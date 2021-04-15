#ifndef ITEMFUNCTION_H
#define ITEMFUNCTION_H

#include <QWidget>
#include "Global.h"
#include "ItemBase.h"
#include "DialogPainter.h"
#include <QTimerEvent>
namespace Ui {
class ItemFunction;
}

class ItemFunction : public ItemBase
{
    Q_OBJECT

public:
    explicit ItemFunction(QWidget *parent = nullptr);
    ~ItemFunction();



private:
    Ui::ItemFunction *ui;

    void timerEvent(QTimerEvent*);

        int m_iTimeSec = 0;

        DialogPainter msg;

signals:
    void sendRefresh();

    void sendPlay(bool b);

private slots:
    void on_btnPause_clicked();

    void on_btnQrcode_clicked();

//    void on_btnOther_clicked();

    void on_btnMsg_clicked();




    void nfc(QString sId);
};

#endif // ITEMFUNCTION_H
