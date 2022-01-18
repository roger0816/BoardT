#ifndef CCTRLFUNC_H
#define CCTRLFUNC_H

#include <QObject>
#include "CData.h"

#define CCTRL CCtrlFunc::Instance()

class CCtrlFunc : public QObject
{
    Q_OBJECT
public:

    void setCtrlSource(CData *dData);

    static CCtrlFunc &Instance();

    void changeLayer(QString sLayerName,bool bStopPlay = true);

    QString layerName();

    QString preLayerName();

private :
    explicit CCtrlFunc(QObject *parent = nullptr);

    static CCtrlFunc* m_pInstance;

    CData *m_data;

    QString m_sPreLayerName="";

signals:
    void callChangePage(QString ,bool );

};

#endif // CCTRLFUNC_H
