#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include <QTimer>
#include "CData.h"
#include <QImage>
#include "ItemBaseContent.h"
#include <QResizeEvent>
#include <QShowEvent>
#include "ItemVideoCon.h"

namespace Ui {
class DisplayWidget;
}

class DisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayWidget(QWidget *parent = nullptr);
    ~DisplayWidget();

    QPixmap setLayer(QString sPath);

    void setEdit(bool b);

    float m_fDiff = 0.50;

    QList<ItemBaseContent*> m_listItem;

    QString m_layerName;

    QString m_sPath;

private:
    Ui::DisplayWidget *ui;

    bool m_bEdit = false;

    int m_iBorderSize = 0;

    void resizeEvent(QResizeEvent *) override;

    void showEvent(QShowEvent *) override;

    void updateItemRect();

    bool checkObjName(QString sObj);

    void refreshBg();

    ItemPlayer *m_video = nullptr;
signals:

    void changeTarget(QString sPath);
public slots:
    void slotFocus();

    void slotUpdate();

    void refreshItem();

    void raiseItem(QString sPath);

    void renameItem(QString sOldPath,QString sNewPath);

    void deleteItem(QString sPath);

    void addItem(int iIdx);
};

#endif // DISPLAYWIDGET_H
