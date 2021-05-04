#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDateTime>
#include "CData.h"
#include "DisplayWidget.h"
#include "LayerNewModel.h"
#include <QColorDialog>
#include "LayerAddContent.h"

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

    void on_btnAddModel_clicked();

    void on_btnAddLayer_clicked();

    void on_btnSave_clicked();

    void on_btnUpload_clicked();

public slots:
    void slotSelector(QString sName);

    void refreshSelector();

private:
    Ui::Widget *ui;

    void upload(QString sIp, QString sTarget, QString sPath);


};
#endif // WIDGET_H
