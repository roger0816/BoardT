#ifndef UDEVMONITOR_H
#define UDEVMONITOR_H

#include <QThread>
#include <QList>
#include <QMutex>
#include <QMutexLocker>
#include <QProcess>
#include <QElapsedTimer>
#include <QTimer>
#include "udev.h"
#include "const_defines.h"

class UdevMonitor : public QThread {
    Q_OBJECT

    static const uint MAX_MOUNTED_COUNT = 2;
    static const uint MAX_WAIT_MOUNTED_TIME = 6000;
public:
    UdevMonitor();
    ~UdevMonitor();
    void stop();
    QStringList &deviceList();

public slots:

signals:
    void deviceAdded(QString mountPoint);
    void deviceRemoved(QString mountPoint);
	void deviceChanged(QString subsys, QString devpath);

protected:
    void run();

private:
    static QMutex mMutex;
    Udev *mUdev;
    QStringList mMedium;

    bool mStopped;
    void addDevice(UdevDevice *device);
    void removeDevice(UdevDevice *device);
	void deviceChange(UdevDevice *device);

    bool addDeviceToDeviceList(const QString &list);
    bool removeDeviceFromDeviceList(const QString &list);
    void showDeviceProperties(UdevDevice *device);
    bool waitDeviceMountChanged();
    QStringList mountedMedium() const;
    bool isReadable(QString path);
    void loadMountedMedium();
};

#endif // UDEVMONITOR_H
