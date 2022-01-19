#ifndef DIALOGEDITGRID_H
#define DIALOGEDITGRID_H

#include <QDialog>
#include <QDebug>
#include <QPixmap>
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

    void slotItemClicked(int);

    void slotG2ItemClicked(int);

    void on_btnG2SetPic_clicked();

    void on_btnG2SetListPic_clicked();

    void on_btnG1Clear_clicked();

    void on_btnG2Clear_clicked();

    void on_btnG3SetPic_clicked();

    void on_btnG3Clear_clicked();

    void on_btnOk_clicked();

private:
    Ui::DialogEditGrid *ui;

    ObjData *m_obj = nullptr;

    int m_iCount= 9;

    void refresh();

    int m_iPreG1Idx =-1;

    int m_iPreG2Idx = -1;
};

#endif // DIALOGEDITGRID_H
