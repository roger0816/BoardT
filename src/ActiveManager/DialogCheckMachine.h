#ifndef DIALOGCHECKMACHINE_H
#define DIALOGCHECKMACHINE_H

#include <QDialog>
#include <QTimerEvent>
#include "ItemCheckMachine.h"
#include <QSettings>
#include "CData.h"
#include <QShowEvent>
namespace Ui {
class DialogCheckMachine;
}

class DialogCheckMachine : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCheckMachine(QWidget *parent = nullptr);
    ~DialogCheckMachine();

private slots:
    void on_btnSave_clicked();

private:
    Ui::DialogCheckMachine *ui;

    void timerEvent(QTimerEvent *) override;

    void showEvent(QShowEvent *) override;

    int m_iSec= 0;

    QList<ItemCheckMachine*> m_listItem;

    QStringList m_listCheckIp;

    void read();

    void write();
};

#endif // DIALOGCHECKMACHINE_H
