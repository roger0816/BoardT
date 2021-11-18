
#include "udevmonitor.h"
#include <QThread>

#include "udevdevice.h"
extern "C" {
#ifndef WIN32
#include <libudev.h>
#endif
}

QMutex UdevMonitor::mMutex;

UdevMonitor::UdevMonitor(): mUdev(new Udev())
{
    mStopped = false;
    mMedium.clear();
    qDebug() << "init UdevMonitor";
}

UdevMonitor::~UdevMonitor()
{
    mStopped = true;
    delete mUdev;
    qWarning() << "~ deconstruct UdevMonitor";
}

void UdevMonitor::run() {

    QTimer::singleShot(7000, this, [=]{
        loadMountedMedium();
    });

    while(!mStopped) {
        UdevDevice *device = mUdev->event();
        QString sysname = QString(device->getSysname());
        const char* devnode = device->getDevnode();
        if (sysname.isEmpty() || devnode == NULL) {
            msleep(100);

			delete device;
			if(!sysname.isEmpty())
				qDebug() << "ignore event : " << sysname;
			if(devnode != NULL)
				qDebug() << "ignore event: " << devnode;

            continue;
        }

        mMutex.lock();
        QString action = device->getAction();
        qInfo() << "action:" << action;
        qInfo() << "Devpath: " << device->getDevpath();
        qInfo() << "Subsystem: " << device->getSubsystem();
        qInfo() << "Devtype: " << device->getDevtype();
        qInfo() << "Syspath: " << device->getSyspath();
        qInfo() << "Sysnum: " << device->getSysnum();
        qInfo() << "Sysname:" << sysname;
        qInfo() << "devnode:" << devnode;
        qInfo() << "DevlinksListEntry: " << device->getDevlinksListEntry();
        qInfo() << "PropertiesListEntry: " << device->getPropertiesListEntry();

        showDeviceProperties(device);

        if (action == "add")
            addDevice(device);
        else if (action == "remove")
            removeDevice(device);
		else if (action == "change")
			deviceChange(device);

        delete device;
        msleep(10);
        mMutex.unlock();
    }
    qDebug() << "UdevMonitor stopped: " << mStopped;
}

void UdevMonitor::stop() {
    mStopped = true;
}

/**
 * @brief UdevMonitor::deviceList the mounted device list
 * @return
 */
QStringList &UdevMonitor::deviceList()
{
    return mMedium;
}

void UdevMonitor::loadMountedMedium()
{
    QStringList list = mountedMedium();
    for(const QString& entry : list) {
        if (!addDeviceToDeviceList(entry))
            continue;

        qInfo() << "media mounted: " << entry;
        deviceAdded(entry);
    }
}

/**
 * @brief UdevMonitor::addDevice just get udev add event
 * @param list mounted list
 */
void UdevMonitor::addDevice(UdevDevice *device)
{
    Q_UNUSED(device);

    qDebug() << "entry addDevice";
    QElapsedTimer timer;
    timer.start();
    uint tryCount = 0;
    // at least try 5 times
    while(tryCount < MAX_MOUNTED_COUNT) {
        if (!waitDeviceMountChanged()) {
            return;
        }
        tryCount++;
        QThread::msleep(500);
    }

    QStringList newList = mountedMedium();
    qDebug() << "addDevice current medium:";
    qDebug() << mMedium;
    qDebug() << "addDevice new medium:";
    qDebug() << newList;
    QSet<QString> subtraction = newList.toSet().subtract(mMedium.toSet());

    foreach (const QString &media, subtraction) {
        qDebug() << "new device is " << media;

        if (addDeviceToDeviceList(media)) {
            qInfo() << "media mounted: " << media;
            deviceAdded(media);
        }
    }
    qDebug() << "exit addDevice " << timer.elapsed() / 1000;
}

/**
 * @brief UdevMonitor::removeDevice just get udev remove event
 * @param list mounted list
 */
void UdevMonitor::removeDevice(UdevDevice *device)
{
    Q_UNUSED(device);
    if (!waitDeviceMountChanged()) {
        qDebug() << "exit removeDevice and no changed, current list: " << mMedium;
        return;
    }

    QStringList newList = mountedMedium();
    qDebug() << "### removeDevice current medium:";
    qDebug() << mMedium;
    qDebug() << "### removeDevice new medium:";
    qDebug() << newList;
    QSet<QString> subtraction = mMedium.toSet().subtract(newList.toSet());
    qDebug() << "subtraction: " << subtraction.size();
    foreach (const QString &media, subtraction) {
        qDebug() << "prepare remove device is " << media;
        if (!removeDeviceFromDeviceList(media)) {
            qWarning() << media << " not remove from current list";
            continue;
        }
        qDebug() << "device " << media << " removed from list";
        deviceRemoved(media);
    }
    qDebug() << "exit removeDevice, current list: " << mMedium;
}

void UdevMonitor::deviceChange(UdevDevice *device)
{
	if(device)
		deviceChanged(device->getSubsystem(), device->getDevpath());
}

bool UdevMonitor::addDeviceToDeviceList(const QString &mountPoint)
{
    if (mMedium.contains(mountPoint)) {
        return false;
    }
    if (!isReadable(mountPoint)) {
        qWarning() << "can not access " << mountPoint;
        return false;
    }
    mMedium.push_back(mountPoint);
    return true;
}

bool UdevMonitor::removeDeviceFromDeviceList(const QString &mountPoint)
{
    if (!mMedium.contains(mountPoint)) {
        return false;
    }
    mMedium.removeAll(mountPoint);
    return true;
}

/**
 * @brief UdevMonitor::mountedMedium Get current mounted medium
 * @return QStringList
 */
QStringList UdevMonitor::mountedMedium() const
{
    QStringList list;
    QProcess cmd;
    cmd.start("/bin/sh", QStringList() << "-c" << "df -ah | grep /media");
    cmd.waitForFinished();
    QStringList lines = ((QString)cmd.readAllStandardOutput()).split("\n");
    cmd.close();

    foreach (QString line, lines) {
        QString media = line.split(" ").last();
        if (media.isEmpty())
            continue;

        list << media;
    }
    qDebug() << "&&&&& mounted media list: " << list;
    return list;
}

bool UdevMonitor::waitDeviceMountChanged()
{
    bool changed = false;
    int maxWaitTime = MAX_WAIT_MOUNTED_TIME;
    int tryTime = 0;
    while(!changed && !mStopped) {
        // wait too long
        if (tryTime >= maxWaitTime)
            break;

        QStringList mediumList = mountedMedium();
        if (mediumList.length() != mMedium.length()) {
            changed = true;
        }
        tryTime += 500;
        QThread::msleep(500);
    }
    return changed;
}

void UdevMonitor::showDeviceProperties(UdevDevice *device)
{
    struct udev_list_entry *sysattrs = device->getPropertiesListEntry();
    struct udev_list_entry* entry;
    udev_list_entry_foreach(entry, sysattrs) {
        const char *name, *value;
        name = udev_list_entry_get_name(entry);
        value = udev_list_entry_get_value(entry);
        qDebug() << name << "=" << value;
    }
}

bool UdevMonitor::isReadable(QString path)
{
    QDir mountDir(path);
    return mountDir.exists() && mountDir.isReadable();
}
