#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include <QTimer>
#include "CData.h"
#include <QImage>
#include "ItemBaseContent.h"
#include <QResizeEvent>
#include <QShowEvent>


namespace Ui {
class DisplayWidget;
}

class DisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayWidget(QWidget *parent = nullptr);
    ~DisplayWidget();

    QPixmap setLayer(QString m_sPath);

    void setEdit(bool b);

    LayerData *m_layerData = nullptr;

    float m_fDiff = 0.50;

    QList<ItemBaseContent*> m_listItem;

private:
    Ui::DisplayWidget *ui;

    bool m_bEdit = false;

    void resizeEvent(QResizeEvent *) override;

    void showEvent(QShowEvent *) override;

    void updateItemRect();
signals:

    void changeTarget(QString sPath);
public slots:
    void slotFocus();

    void slotUpdate();

    void refreshItem();

    void raiseItem(QString sPath);

    void renameItem(QString sOldPath,QString sNewPath);
};

#endif // DISPLAYWIDGET_H
