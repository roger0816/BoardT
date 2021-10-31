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

    void readData(QString sPath);

    void writeData();

    QString m_sWaitRename = "";

    QString m_sObjPath;

    QString m_sName;

    QString m_sLayerName;

    QRect m_rect;

    QString m_sType;

    QMap<QString,QVariant> m_data;

    QVariantMap m_dEditData; // just edit temp data

   // DataText m_dataText;

    DataPic m_dataPic;

    DataVideo m_dataVideo;

    DataGrid m_dataGrid;


    //DataMar m_dataMar;

    DataCmd m_dataCmd;

    QMap<QString,int> m_dDefine;


private:


    bool deleteDirectory(const QString &path);





signals:

};

#endif // OBJDATA_H
