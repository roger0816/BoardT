#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

#include <QObject>
#include <QTimer>
#include "CData.h"
#include "CCtrlFunc.h"



struct dataMuti
{
    QString sName;

    QDateTime m_dateTime;


};

class ScheduleManager : public QObject
{
    Q_OBJECT
public:
    explicit ScheduleManager(QObject *parent = nullptr);


    void check(int iMsec=1000);

private:

    void readConfig();

    bool multiSchedule(QString &sLayerName);

    bool oneSchedule(QString &sLayerName);

    bool checkSleep();


    int m_iDefineSubMsec=1000;


private:


    int m_iType = -1;

    QStringList m_listMulti;

    QStringList m_listOne;

    QStringList m_listSleep;

    int m_iMultiIdx = -1;

    int m_iMultiDelay=0;

    QString m_bPreLayer="";

    bool m_bSleep= false;



signals:


};

#endif // SCHEDULEMANAGER_H
