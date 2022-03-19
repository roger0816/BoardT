#ifndef DIALOGCHECKMACHINE_H
#define DIALOGCHECKMACHINE_H

#include <QDialog>
#include <QTimerEvent>
#include "ItemCheckMachine.h"
namespace Ui {
class DialogCheckMachine;
}

class DialogCheckMachine : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCheckMachine(QWidget *parent = nullptr);
    ~DialogCheckMachine();

private:
    Ui::DialogCheckMachine *ui;

    void timerEvent(QTimerEvent *) override;

    int m_iSec= 0;

    QList<ItemCheckMachine*> m_listItem;

    QStringList m_listCheckIp;
};

#endif // DIALOGCHECKMACHINE_H
