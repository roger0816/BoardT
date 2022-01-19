#ifndef LAYERNEWMODEL_H
#define LAYERNEWMODEL_H

#include <QWidget>
#include <QDialog>
#include <QFileDialog>
#include <QDir>
#include <QDebug>

namespace Ui {
class LayerNewModel;
}

class LayerNewModel : public QDialog
{
    Q_OBJECT

public:
    explicit LayerNewModel(QWidget *parent = nullptr);
    ~LayerNewModel();

    void setPath(QString sTitle,QString sPath);

    QString m_sModelPath;

private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

    void on_btnSelect_clicked();

private:
    Ui::LayerNewModel *ui;
};

#endif // LAYERNEWMODEL_H
