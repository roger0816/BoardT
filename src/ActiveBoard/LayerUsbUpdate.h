#ifndef LAYERUSBUPDATE_H
#define LAYERUSBUPDATE_H

#include <QWidget>
#include <QShowEvent>
#include <QTimerEvent>
#include <QDir>
#include <QDebug>

namespace Ui {
class LayerUsbUpdate;
}

class LayerUsbUpdate : public QWidget
{
    Q_OBJECT

public:
    explicit LayerUsbUpdate(QWidget *parent = nullptr);
    ~LayerUsbUpdate();


    void showEvent(QShowEvent *) override;

    bool m_bCanDoit = false;

    bool m_bLock = false;

    void setUsbList(QStringList listUsb);

    void doUpdate();

private:
    Ui::LayerUsbUpdate *ui;

    void detectUsb();

    bool checkPath(QString sPath);

    QStringList m_listUsb;

    void timerEvent(QTimerEvent *) override;
};

#endif // LAYERUSBUPDATE_H
