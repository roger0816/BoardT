#ifndef FUNCUSB_H
#define FUNCUSB_H

#include <QObject>
#include <QDebug>
#include <QProcess>
#include <QTimer>
#include <QSettings>

class FuncUsb : public QObject
{
    Q_OBJECT
public:
    explicit FuncUsb(QObject *parent = nullptr);

    bool checkUsb(QString sUuid);

    bool isDevelop(QString sUuid="");

    bool differentDevUsb(QString sUuid);

    bool isReg();

    void writeReg(QString sUuid);

    void removeReg();

    bool isLogin(QString sTarget="");

    QString m_sLastUsbPath;

private:
    QTimer m_timer;

    QMap<QString,QString> m_dData;

    bool m_bFirstTime = true;

signals:
    void usbChange(QString sUuid,QString sPath,bool bPlunIn);
private slots:

    void timerout();

    void test(QString sUuid,QString sPath,bool bPlunIn);

};

#endif // FUNCUSB_H
