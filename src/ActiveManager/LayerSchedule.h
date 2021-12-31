#ifndef LAYERSCHEDULE_H
#define LAYERSCHEDULE_H

#include <QWidget>
#include <QTimeEdit>
#include <QTimer>
#include <QTime>
#include <QComboBox>
#include <QDebug>
#include <QFile>
#include <QShowEvent>
#include "DialogMsg.h"
#include "CData.h"
#include <QSettings>
#include <QRadioButton>
namespace Ui {
class LayerSchedule;
}

class LayerSchedule : public QWidget
{
    Q_OBJECT

public:
    explicit LayerSchedule(QWidget *parent = nullptr);
    ~LayerSchedule();

private:
    Ui::LayerSchedule *ui;

    QString m_sCurrentLayerName = "";


    void tbAdd(int iIdxPage=0,QString sTime="00:10:00",int iIsPlay=0);


    void showEvent(QShowEvent *) override;

    void save();

    void read();

    int rbIndex();

    void setRbIndex(int idx);

    QList<QRadioButton*> m_listRb;
public slots:
    void slotSelector(QString sName);


private slots:
    void on_btnAdd_clicked();
    void on_btnDel_clicked();

    void on_rbNone_clicked();
    void on_rbMuti_clicked();
    void on_rbOne_clicked();
};

#endif // LAYERSCHEDULE_H
