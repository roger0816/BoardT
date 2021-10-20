#ifndef DIALOGEDITGRID_H
#define DIALOGEDITGRID_H

#include <QDialog>
#include <QDebug>
#include <QGridLayout>
#include <QShowEvent>
#include <QResizeEvent>
#include <QFileDialog>
#include "DialogMsg.h"
#include "ObjData.h"

namespace Ui {
class DialogEditGrid;
}

class DialogEditGrid : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditGrid(QWidget *parent = nullptr);
    ~DialogEditGrid();

    void setObj(ObjData *obj);

private:
    void showEvent(QShowEvent* )override;

    void resizeEvent(QResizeEvent* )override;
    void resetSize();

private slots:
    void on_btnG1SetListPic_clicked();

    void on_btnG1SetPic_clicked();

    void slotItemClicked(int i);

    void slotG2ItemClicked(int i);

private:
    Ui::DialogEditGrid *ui;

    ObjData *m_obj = nullptr;

    int m_iCount= 9;
};

#endif // DIALOGEDITGRID_H
