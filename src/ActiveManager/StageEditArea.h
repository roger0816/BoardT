#ifndef STAGEEDITAREA_H
#define STAGEEDITAREA_H

#include <QWidget>
#include <QDebug>
#include <QShowEvent>
#include "LayerNewModel.h"


namespace Ui {
class StageEditArea;
}

class StageEditArea : public QWidget
{
    Q_OBJECT

public:
    explicit StageEditArea(QWidget *parent = nullptr);
    ~StageEditArea();

private slots:
    void on_btnBack_clicked();


    void on_btnAddLayer_clicked();

    void on_btnRemoveLayer_clicked();


    void on_btnSave_clicked();

    void on_btnUpload_clicked();

    void on_btnView_clicked();

    void slotSelector(QString sName);



    void on_btnLayerBg_clicked();

    void on_btnDelLayerBg_clicked();

private:
    Ui::StageEditArea *ui;

    void refreshSelector(bool bToDef = false);

    void showEvent(QShowEvent *) override;

    QString m_sPreIp;

signals:
    void sendBack();

};

#endif // STAGEEDITAREA_H
