#ifndef LAYERUSBUPDATE_H
#define LAYERUSBUPDATE_H

#include <QWidget>
#include <QShowEvent>

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

    void setUsbList(QStringList listUsb);

private:
    Ui::LayerUsbUpdate *ui;

    void detectUsb();

    QStringList m_listUsb;

};

#endif // LAYERUSBUPDATE_H
