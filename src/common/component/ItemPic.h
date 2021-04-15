#ifndef ITEMPIC_H
#define ITEMPIC_H

#include <QWidget>
#include <QLabel>
#include "Global.h"
#include "ItemBase.h"

class ItemPic : public ItemBase
{
    Q_OBJECT
public:
    explicit ItemPic(QWidget *parent = nullptr);

    bool init() override;

    void setPic(QString sFilePath);

    void setText(QString sText);

    QLabel *m_lb;

    void resizeEvent(QResizeEvent *);

signals:

public slots:
};

#endif // ITEMPIC_H
