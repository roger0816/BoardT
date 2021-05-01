#ifndef LAYER_DATA_H
#define LAYER_DATA_H

#include <QObject>

#include "ObjData.h"

#include "Voj.h"

#include <QImage>
#include <QPixmap>

class LayerData : public QObject
{
    Q_OBJECT
public:
    explicit LayerData(QObject *parent = nullptr);

    void setPath(QString sPath);

    QString m_sLayerPath;

    QString m_sName;

    QString m_sBgPath;

    QPixmap m_scaleImage;


    QList<ObjData*> m_listData;

    QMap<QString,int> m_dDefine;


private:



signals:

};


#endif // OBJDATA_H
