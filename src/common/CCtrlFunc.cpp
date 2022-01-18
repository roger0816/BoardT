#include "CCtrlFunc.h"

CCtrlFunc *CCtrlFunc::m_pInstance = nullptr;



CCtrlFunc::CCtrlFunc(QObject *parent) : QObject(parent)
{

}

void CCtrlFunc::setCtrlSource(CData *dData)
{
    m_data = dData;

}

CCtrlFunc &CCtrlFunc::Instance()
{
    if(m_pInstance==nullptr)
        m_pInstance = new CCtrlFunc();

    return *m_pInstance;
}

void CCtrlFunc::changeLayer(QString sLayerName, bool bStopPlay)
{
      m_sPreLayerName = layerName();

      emit callChangePage(sLayerName,bStopPlay);
}

QString CCtrlFunc::layerName()
{
    return m_data->m_sCurrentLayerName;
}

QString CCtrlFunc::preLayerName()
{
    return m_sPreLayerName;
}
