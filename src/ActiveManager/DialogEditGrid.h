#ifndef DIALOGEDITGRID_H
#define DIALOGEDITGRID_H

#include <QDialog>
#include <QDebug>
#include <QGridLayout>
#include <QShowEvent>
#include <QResizeEvent>
#include <QFileDialog>
#include "DialogMsg.h"

namespace Ui {
class DialogEditGrid;
}

class DialogEditGrid : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditGrid(QWidget *parent = nullptr);
    ~DialogEditGrid();

    void showEvent(QShowEvent* )override;

    void resizeEvent(QResizeEvent* )override;
    void resetSize();

private slots:
    void on_btnG1SetListPic_clicked();

    void on_btnG1SetPic_clicked();

private:
    Ui::DialogEditGrid *ui;
};

#endif // DIALOGEDITGRID_H
