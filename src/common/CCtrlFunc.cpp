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
      qDebug()<<"AAA1";
    emit callChangePage(sLayerName,bStopPlay);
}
