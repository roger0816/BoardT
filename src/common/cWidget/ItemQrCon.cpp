#include "ItemQrCon.h"

ItemQrCon::ItemQrCon(QWidget *parent) : ItemBaseObj(parent)
{
        m_lb = new QLabel(this);

}

void ItemQrCon::updateItem()
{
    QString sText= m_obj->m_dataText.sText;

    if(sText.trimmed().length()<1)
    {
        m_lb->setStyleSheet("background-color:gray;");

        m_lb->setPixmap(QPixmap());

        return ;

    }

    QRecLevel level = QR_ECLEVEL_H;

    QRencodeMode mode = QR_MODE_8;

    QByteArray bsharecode = sText.toUtf8();


    QRcode *code = QRcode_encodeString(sText.toLatin1(), 7, level, mode, 1);


    QPixmap pix = drawImageQr(code);

    m_lb->setStyleSheet("background-color:white");

    m_lb->setPixmap(pix);


    show();


}

QPixmap ItemQrCon::drawImageQr(QRcode *code)
{

    unsigned char *point = code->data;

    double d= width()-40;

    double scale = d* 1.0/ code->width;
    qDebug()<<"scale : "<<scale;
    QPixmap pixmap(width(),width());

    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor("#000000")));

    for (int y = 0; y < code->width; y ++)
    {
        for (int x = 0; x < code->width; x ++)
        {
            if (*point & 1)
            {
                QRectF r(x * scale+15, y * scale+15, scale, scale);
                painter.drawRects(&r, 1);
            }
            point ++;
        }
    }

    return pixmap;

}

void ItemQrCon::reSetSize()
{
    m_lb->resize(width(),width());

    updateItem();
}
