#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QDateTime>
#include "CData.h"
#include "LayerData.h"
#include "DisplayWidget.h"
#include "LayerNewModel.h"
#include <QColorDialog>
#include "LayerAddContent.h"
#include <QProcess>
#include "DialogUploadUsb.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void loadModel(QString sPath);

    QString m_sPreIp="";
private slots:

    void on_btnSelectModel_clicked();


    void on_btnSave_clicked();

    void on_btnUpload_clicked();

    void on_btnTest_clicked();


    void on_btnTry_clicked();

    void on_btnLayerBg_clicked();

    void on_btnDelLayerBg_clicked();

    void on_btnEdit_clicked();

    void on_btnSetting_clicked();

    void on_btnSchedule_clicked();

    void on_btnTimeSchedule_clicked();




    void on_rdNoneSchedule_clicked();

    void on_rdSchedule_clicked();

    void on_rdTimeSchedule_clicked();


    void on_btnUploadUsb_clicked();

public slots:
    void slotSelector(QString sName);


private:
    Ui::Widget *ui;

    void upload(QString sIp, QString sTarget, QString sPath);

    QButtonGroup m_listButtonStack;

 //   void rename(QString sOld,QString sNew);

    void StageEditback();
 //  void refreshTimeSchedule();


};
#endif // WIDGET_H
