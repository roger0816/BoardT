#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "CData.h"
#include "DisplayWidget.h"
#include "LayerNewModel.h"
#include <QColorDialog>

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


private slots:

    void on_btnSelectModel_clicked();

    void on_btnAddModel_clicked();

    void on_btnAddLayer_clicked();

public slots:
    void slotSelector(QString sName);

    void refreshSelector();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
