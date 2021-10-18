#ifndef ITEMDATETIME_H
#define ITEMDATETIME_H

#include <QWidget>
#include "ItemLabel.h"
#include <QDateTime>
#include <QTimerEvent>

class ItemDateTime : public ItemLabel
{
    Q_OBJECT

public:
    explicit ItemDateTime(QWidget *parent = nullptr);
    ~ItemDateTime();

    int m_iChangeTime = 3;

    void setString(QString sDate,QString sTime);

    void updateItem() override;

private:

    void timerEvent(QTimerEvent* ) override;

    int m_iSec = 0;

    bool m_bCurrentShowDate = true;

    void change();

    QString m_sDate = "yyyy/MM/dd";

    QString m_sTime = "hh:mm:ss";

};

#endif // ITEMDATETIME_H
