#ifndef LAYERTIMESCHEDULE_H
#define LAYERTIMESCHEDULE_H

#include <QWidget>
#include <QDebug>
#include "CData.h"

namespace Ui {
class LayerTimeSchedule;
}

class LayerTimeSchedule : public QWidget
{
    Q_OBJECT

public:
    explicit LayerTimeSchedule(QWidget *parent = nullptr);
    ~LayerTimeSchedule();

    void refreshTimeSchedule();

    void on_cbTimeDayOfWeek_currentIndexChanged(int index);


    void on_teTo_userTimeChanged(const QTime &time);


    void on_cbStopPreVideo_clicked();


    void on_teFrom_timeChanged(const QTime &time);

    void setTimeData(QString sLayerName);




    bool m_bLockTimeSend = false;

private slots:

private:
    Ui::LayerTimeSchedule *ui;
};

#endif // LAYERTIMESCHEDULE_H
