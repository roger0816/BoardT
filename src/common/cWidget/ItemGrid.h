#ifndef ITEMGRID_H
#define ITEMGRID_H

#include <QWidget>
#include "ItemBaseObj.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QGridLayout>

enum GRID_TYPE
{
    GRID4,
    GRID6,
    GRID9

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

    void setType(GRID_TYPE type);

    QButtonGroup m_listButton;

private:
    Ui::ItemGrid *ui;
};

#endif // ITEMGRID_H
