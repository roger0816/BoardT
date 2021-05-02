#ifndef LAYERADDCOMPONT_H
#define LAYERADDCOMPONT_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QFileDialog>
#include "Voj.h"

namespace Ui {
class LayerAddContent;
}




class LayerAddContent : public QWidget
{
    Q_OBJECT

public:
    explicit LayerAddContent(QWidget *parent = nullptr);
    ~LayerAddContent();

private:
    Ui::LayerAddContent *ui;

    QList<QPushButton*> m_listBtn;

private slots:

    void slotClicked();

signals:
    void btnAddClicked(int iIdx);
};

#endif // LAYERADDCOMPONT_H
