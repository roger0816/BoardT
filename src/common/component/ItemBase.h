#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QWidget>
#include "Global.h"
#include <QMouseEvent>

class ItemBase : public QWidget
{
    Q_OBJECT
public:
    explicit ItemBase(QWidget *parent = nullptr);

    void setPath(QString sPath);

    virtual bool init(){return false;}

    void mousePressEvent(QMouseEvent * ) override;

    void timerEvent(QTimerEvent* ) override;

    QVariant config(QString Key);

    QString m_sPath;


signals:

public slots:
};

#endif // ITEMBASE_H
