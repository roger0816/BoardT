#ifndef EDITGRID_H
#define EDITGRID_H

#include <QWidget>
#include "EditBase.h"
#include "ObjData.h"
#include "DialogEditGrid.h"

namespace Ui {
class EditGrid;
}

class EditGrid : public EditBase
{
    Q_OBJECT

public:
    explicit EditGrid(QWidget *parent = nullptr);
    ~EditGrid();

    void setTarget(ObjData *obj);

private slots:
    void on_btnSet_clicked();

    void on_cbSelect_currentIndexChanged(int index);

private:
    Ui::EditGrid *ui;
};

#endif // EDITGRID_H
