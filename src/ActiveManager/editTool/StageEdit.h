#ifndef STAGEEDIT_H
#define STAGEEDIT_H

#include <QWidget>
#include <QToolBox>
#include <QPushButton>
#include "ItemContent.h"
#include "LayerNewModel.h"
#include <QFileDialog>
#include <QApplication>
#include <QSettings>
#include <QProcess>
#include <QFile>

#include "DisplayContent.h"
#include "DialogMsg.h"
#include <QDateTime>


//logo=11

//ticket=12

//active=13

//onSale=14

//mediaCent=17


namespace Ui {
class StageEdit;
}

class StageEdit : public QWidget
{
    Q_OBJECT

public:
    explicit StageEdit(QWidget *parent = nullptr);
    ~StageEdit();

    QString m_sPath;

    void editType(int i);

private slots:
    void on_btnLabel_clicked();



    void on_btnToTop_clicked();

    void on_btnCreate_clicked();

    void on_btnSave_clicked();

    void on_btnOpen_clicked();

    void on_btnRename_clicked();


    void on_btnTest_clicked();

    void on_btnMainBg_clicked();

    void on_sbX_valueChanged(int arg1);

    void on_sbY_valueChanged(int arg1);

    void on_sbW_valueChanged(int arg1);

    void on_sbH_valueChanged(int arg1);

    void on_btnUpload_clicked();

    void upload(QString sIp,QString sTarget,QString sPath="/home/pi/work/bin/data");

private:
    Ui::StageEdit *ui;


    QMap<QString,int> m_dDefine;


    DisplayContent *m_wTarget = nullptr;

    void checkDir();

    QString m_sPreIp="";

public slots:
    void slotItemUpdate();

    void slotEditChange();




};

#endif // STAGEEDIT_H
