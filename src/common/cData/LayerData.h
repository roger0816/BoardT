#ifndef LAYER_DATA_H
#define LAYER_DATA_H

#include <QObject>

#include "ObjData.h"

#include "Voj.h"

class LayerData : public QObject
{
    Q_OBJECT
public:
    explicit LayerData(QObject *parent = nullptr);

    void setPath(QString sPath);

    QString m_sLayerPath;

    QString m_sName;

    QString m_sBgPath;



    QList<ObjData*> m_listData;

    QMap<QString,int> m_dDefine;


private:



signals:

};


#endif // OBJDATA_H
