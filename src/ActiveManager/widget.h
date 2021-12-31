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
#include "CCtrlFunc.h"

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

    void goUploadPage(QString sPath);

    QString m_sPreIp="";
private slots:


public slots:

private:
    Ui::Widget *ui;


    void StageEditback();



};
#endif // WIDGET_H
