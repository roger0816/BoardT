#include "StageEditArea.h"
#include "ui_StageEditArea.h"

StageEditArea::StageEditArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageEditArea)
{
    ui->setupUi(this);
}

StageEditArea::~StageEditArea()
{
    delete ui;
}

void StageEditArea::refreshSelector(bool bToDef)
{
    qDebug()<<"re selector";

    QStringList listKey = CDATA.m_dData.keys();

    qDebug()<<"listkey "<<listKey;

    qDebug()<<CDATA.m_dData;

    DisplayWidget w;

    QMap <QString , QPixmap> dPix;

    for(int i=0;i<listKey.length();i++)
    {

        dPix.insert(listKey[i], w.setLayer(CDATA.m_dData[listKey.at(i)]->m_sLayerPath));

    }

    ui->wLayerSelector->setData(dPix,CDATA.m_sPath);

    if(bToDef)
    {
        ui->wLayerSelector->toDef();
    }
}

void StageEditArea::showEvent(QShowEvent *event)
{
    qDebug()<<"show event : StageEditArea";

    refreshSelector();
}

void StageEditArea::on_btnBack_clicked()
{
    emit sendBack();
}
