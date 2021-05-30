#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

#include <QObject>
#include "CData.h"

class ScheduleManager : public QObject
{
    Q_OBJECT
public:
    explicit ScheduleManager(QObject *parent = nullptr);

    void startModel(QString sPath);



    bool checkTimeSchedule();

    QString m_sPath;

    QString m_sCurrentLayer;

signals:

};

#endif // SCHEDULEMANAGER_H
