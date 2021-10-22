#ifndef ITEMGRID_H
#define ITEMGRID_H

#include <QWidget>
#include "ItemBaseObj.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QGridLayout>

enum GRID_TYPE
{
    GRID4=4,
    GRID6=6,
    GRID9 =9

};


namespace Ui {
class ItemGrid;
}

class ItemGrid : public ItemBaseObj
{
    Q_OBJECT

public:
    explicit ItemGrid(QWidget *parent = nullptr);
    ~ItemGrid();

    void updateItem() override;


private:

    void reSetSize() override;

    QButtonGroup m_listButton;

 //   QPushButton *m_btnMain;

    QPushButton *m_btnBack;

    Ui::ItemGrid *ui;

    GRID_TYPE m_type = GRID9;

    int m_iCurrentLv = 1;


    QButtonGroup m_btns;

    int m_iIdxLv1=0;

    int m_iIdxLv2=0;

    void refresh();
private slots:

    void slotClick(QAbstractButton *btn);

    void slotBack();
};

#endif // ITEMGRID_H
