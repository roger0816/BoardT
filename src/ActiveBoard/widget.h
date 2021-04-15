#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSettings>
#include <QDebug>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>
#include <QFile>
#include "Global.h"
#include "LayerContent.h"
#include <QTimerEvent>
#include <QResizeEvent>

static QString RDATA = "../bin/data";

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void loadConfig(QString sLayer);


    QFileInfoList m_listDir;

    QList<LayerContent*> m_listContent;

    void resizeEvent(QResizeEvent *) override;


    QString m_sTestModel="";

private:
    QString m_sRegUuid="";

    QMap<QString ,int > m_dDefine;



    QString m_sCurrentVerDateTime="";

    QString m_sCurrentBoard="";

    QTimer m_timer;

private slots:

    void loadingLicense();


    void launch(int iIdx =0);

    void refresh();

    void usbChange(QString sUuid,QString sPath,bool bPlugIn);

    void on_btn_clicked();

    void on_btnReReg_clicked();

    void on_btnFacLogin_clicked();

    void on_btnUpdateData_clicked();

    void on_btnUpdateSys_clicked();

    void on_btnBack_clicked();

    void on_btnReboot_clicked();

    void slotTimer();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
