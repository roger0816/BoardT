#ifndef LAYEREDITGRID_H
#define LAYEREDITGRID_H

#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QShowEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QGridLayout>
#include <QButtonGroup>
#include "ObjData.h"


namespace Ui {
class LayerEditGrid;
}

class LayerEditGrid : public QWidget
{
    Q_OBJECT

public:
    explicit LayerEditGrid(QWidget *parent = nullptr);
    ~LayerEditGrid();

    void setObj(ObjData *obj);

    void setListPic(QStringList list);

    void setPic(QString sFilePath, int iIdx=-1);

    int currentId(){return m_listBtns.checkedId();}


private:


    int m_iGridCount =9;

    void showEvent(QShowEvent* ) override;

    void resizeEvent(QResizeEvent *) override;

    void resetSize();

    QButtonGroup m_listBtns;

    QGridLayout *lay ;
signals:
    void clicked(int id);

private:
    Ui::LayerEditGrid *ui;

    ObjData *m_obj = nullptr;

public slots:

   // void slotClicked();

    void slotClicked(QAbstractButton *);
};

#endif // LAYEREDITGRID_H
