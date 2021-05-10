#ifndef ITEMQRCON_H
#define ITEMQRCON_H

#include <QObject>
#include <QWidget>
#include "ItemBaseObj.h"
#include "qrencode.h"
#include <QPainter>
#include <QLabel>
class ItemQrCon : public ItemBaseObj
{
    Q_OBJECT
public:
    explicit ItemQrCon(QWidget *parent = nullptr);

    void updateItem() override;

    QPixmap drawImageQr(QRcode *code);

    void reSetSize() override;

    QLabel *m_lb;


signals:

};

#endif // ITEMQRCON_H
