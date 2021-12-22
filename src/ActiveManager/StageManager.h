#ifndef STAGEMANAGER_H
#define STAGEMANAGER_H

#include <QWidget>
#include <QDebug>
#include "IconButton.h"
#include <QCheckBox>
#include <QButtonGroup>
#include <QGridLayout>
#include <QDir>
#include <QFileInfo>
#include "DialogMsg.h"
#include "DialogDownload.h"
#include "CData.h"
namespace Ui {
class StageManager;
}

class StageManager : public QWidget
{
    Q_OBJECT

public:
    explicit StageManager(QWidget *parent = nullptr);
    ~StageManager();

private slots:
    void on_btnNewModel_clicked();

  //d  void addData(QStringList list,bool bNew = true);
    void on_btnDelete_clicked();

    void on_btnEdit_clicked();

    void slotBtnUpload();

    void slotBtnDowload();


 //   void slotRadioClicked(int);


    void addModel(QString sName);

    void removeModel(QString sName);

    void renameModel(QString sOld,QString sName);
    void slotRadioClicked(QAbstractButton *);

private:
    Ui::StageManager *ui;

    QButtonGroup m_listBtn;

    QStringList m_listKey;

    QGridLayout *m_lay;

    QString m_sPreIp;

    void refresh();

    void showEvent(QShowEvent *) override;

signals:
    void sendSelectModel(QString sPath);


};

#endif // STAGEMANAGER_H
