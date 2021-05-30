#include "LayerTimeSchedule.h"
#include "ui_LayerTimeSchedule.h"

LayerTimeSchedule::LayerTimeSchedule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerTimeSchedule)
{
    ui->setupUi(this);
}

LayerTimeSchedule::~LayerTimeSchedule()
{
    delete ui;
}

void LayerTimeSchedule::setTimeData(QString sLayerName)
{

    ui->lbLayerNameForTime->setText(sLayerName);

   if(CDATA.m_dData.value(sLayerName) == nullptr)
       return ;


    m_bLockTimeSend = true;


    DataLayer data = CDATA.m_dData.value(sLayerName)->m_dataLayer;

    qDebug()<<"scheduleFrom :" <<data.timeScheduleFrom;

    ui->teFrom->setTime(data.timeScheduleFrom);

    ui->teTo->setTime(data.timeScheduleTo);

    ui->cbTimeDayOfWeek->setCurrentIndex(qBound(0,data.dayOfWeek-1,7));

    ui->cbStopPreVideo->setChecked(data.bStopPreVideo);

    m_bLockTimeSend = false;
}


void LayerTimeSchedule::refreshTimeSchedule()
{

    if(m_bLockTimeSend)
        return ;


    if(CDATA.m_dData[ui->lbLayerNameForTime->text()] == nullptr)
    return;
    LayerData *layer =CDATA.m_dData.value(ui->lbLayerNameForTime->text());

   layer->m_dataLayer.timeScheduleFrom =  ui->teFrom->time();

   qDebug()<<layer->m_dataLayer.timeScheduleFrom;

   layer->m_dataLayer.timeScheduleTo = ui->teTo->time();

    layer->m_dataLayer.dayOfWeek = ui->cbTimeDayOfWeek->currentIndex();

    layer->m_dataLayer.bStopPreVideo = ui->cbStopPreVideo->isChecked();
  //  layerData->


}

void LayerTimeSchedule::on_cbTimeDayOfWeek_currentIndexChanged(int index)
{
    refreshTimeSchedule();
}

void LayerTimeSchedule::on_teTo_userTimeChanged(const QTime &time)
{
    refreshTimeSchedule();
}

void LayerTimeSchedule::on_cbStopPreVideo_clicked()
{
    refreshTimeSchedule();
}

void LayerTimeSchedule::on_teFrom_timeChanged(const QTime &time)
{
     refreshTimeSchedule();
}
