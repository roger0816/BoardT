#ifndef CCMD_H
#define CCMD_H

#include <QObject>

#include <QSettings>

#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QDateTime>

#include "../common/cData/Voj.h"

class cCmd : public QObject
{
    Q_OBJECT
public:
    explicit cCmd(QObject *parent = nullptr);

    void callCmd(QString sCmd,QString sValue);


    QStringList m_listCmd={"change","raise","test"};

signals:

};

#endif // CCMD_H
