#ifndef ITEMCHECKMACHINE_H
#define ITEMCHECKMACHINE_H

#include <QWidget>
#include <QProcess>
#include <QDebug>
#include <QTimerEvent>
#include <QDir>
#include <QLabel>
#include <QFileInfo>
#include <QFile>
#include <QMouseEvent>
#include "DialogPicDetail.h"
#include "DialogMsg.h"

namespace Ui {
class ItemCheckMachine;
}

class LabelCheckMachine :public QLabel
{
    Q_OBJECT
public:
    explicit LabelCheckMachine(QWidget *parent = nullptr):QLabel(parent){};
    void mousePressEvent(QMouseEvent *) override{ emit clicked();}
signals:
    void clicked();
};


class ItemCheckMachine : public QWidget
{
    Q_OBJECT

public:
    explicit ItemCheckMachine(QWidget *parent = nullptr);
    ~ItemCheckMachine();

    QString ip();

public slots:
    void check();


private:
    Ui::ItemCheckMachine *ui;

    QString m_sIp;


    QString m_sUser;

    QString m_sPassword;

    QString m_sPicPath;


    int m_iSec = 0;

    QProcess *m_cmd;

    bool deleteDirectory(const QString &path);

    QString mkdir(QString sPath="");

    QString getDeviceInfo();

    void setDeviceInfo();

    void getScreen();

    void pingOk(bool bOk);

    void cmd(QString st);

    bool m_bPicOk = false;

    void connectOk(bool bOk);

private slots:
    void slotFinish(int);

    void slotClicked();

    void on_btnChangeName_clicked();
    void on_btnReboot_clicked();
};

#endif // ITEMCHECKMACHINE_H
