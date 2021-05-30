#ifndef LAYERSCHEDULE_H
#define LAYERSCHEDULE_H

#include <QWidget>
#include <QTimeEdit>
#include <QTimer>
#include <QComboBox>
#include <QDebug>
#include <QFile>
#include <QShowEvent>
#include "DialogMsg.h"
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

    void setData(QStringList list ,int iRow);

    void writeFile(QString sFileName );

    void readFile(QString sFileName );

    void showEvent(QShowEvent *) override;

public slots:
    void slotSelector(QString sName);

     void saveSchedule();
private slots:
    void on_btnAdd_clicked();
    void on_btnDel_clicked();

};

#endif // LAYERSCHEDULE_H
