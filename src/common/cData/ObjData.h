#ifndef OBJDATA_H
#define OBJDATA_H

#include <QObject>
#include "Voj.h"
#include <QDebug>
#include <QSize>
#include <QPoint>
#include <QColor>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QSettings>
#include <QRect>


class ObjData : public QObject
{
    Q_OBJECT
public:
    explicit ObjData(QObject *parent = nullptr);

    void setPath(QString sPath);

    QString m_sObjPath;

    QString m_sName;

    QRect m_rect;

    int iType;

    QMap<QString,int> m_dDefine;

private:

    DataText m_dataText;





signals:

};

#endif // OBJDATA_H
