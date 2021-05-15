#ifndef OBJDATA_H
#define OBJDATA_H

#include <QObject>
#include <QApplication>
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

    QString m_sLayerName;

    QRect m_rect;


    QString m_sType;


    DataText m_dataText;

    DataPic m_dataPic;

    DataVideo m_dataVideo;

    DataMar m_dataMar;

    DataCmd m_dataCmd;

    QMap<QString,int> m_dDefine;


private:






signals:

};

#endif // OBJDATA_H
