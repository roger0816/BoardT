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

    void addData(QStringList list,bool bNew = true);
    void on_btnDelete_clicked();

    void on_btnEdit_clicked();

private:
    Ui::StageManager *ui;

    QButtonGroup m_listBtn;

    QStringList m_listKey;

    QGridLayout *m_lay;

signals:
    void sendSelectModel(QString sPath);


};

#endif // STAGEMANAGER_H