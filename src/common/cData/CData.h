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
#include <QApplication>
#include <QDateTime>

static QString DEF_LAYER_NAME = "def";

static QString BK_LAYER_NAME ="bk";
#define CDATA CData::Instance()


class CData : public QObject
{
    Q_OBJECT
public:

    static CData &Instance();

    void createModel(QString sPath);

    void readModel(QString sPath);

    void writeModel(QString defLayer=DEF_LAYER_NAME);

    void checkDefine();

    void addLayer(QString sPath);

    void removeLayer(QString sPath);

    QMap < QString , LayerData*> m_dData;

    QString m_sPath;

    QString m_sModelName;

    QString m_sCurrentLayerName="";

    QMap<QString,int> m_dDefine;

    ObjData* getObj(QString layer, QString objName, bool &bOk);



private:
    CData(QObject *parent = nullptr);
    static CData* m_pInstance;


    void typeMapping();

    void writeObj(ObjData *item);


    bool deleteDirectory(const QString &path);


signals:

};

#endif // CDATA_H
