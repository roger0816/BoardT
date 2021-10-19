#ifndef EDITGRID_H
#define EDITGRID_H

#include <QWidget>

namespace Ui {
class EditGrid;
}

class EditGrid : public QWidget
{
    Q_OBJECT

public:
    explicit EditGrid(QWidget *parent = nullptr);
    ~EditGrid();

private:
    Ui::EditGrid *ui;
};

#endif // EDITGRID_H
