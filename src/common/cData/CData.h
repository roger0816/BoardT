#ifndef CDATA_H
#define CDATA_H

#include <QObject>
#include "LayerData.h"
#include "ObjData.h"
#include "Voj.h"
#include <QDebug>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>


#define CDATA CData::Instance()


class CData : public QObject
{
    Q_OBJECT
public:

    static CData &Instance();

    void load(QString sPath);

    QMap < QString , LayerData* > m_dData;

    QString m_sPath;


private:
    CData(QObject *parent = nullptr);
    static CData* m_pInstance;


    void typeMapping();

    QMap<QString,int> m_dDefine;



signals:

};

#endif // CDATA_H
