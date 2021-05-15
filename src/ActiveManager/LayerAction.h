#ifndef LAYERACTION_H
#define LAYERACTION_H

#include <QWidget>
#include <QDebug>
#include <QButtonGroup>
#include <QShowEvent>
#include "CData.h"

namespace Ui {
class LayerAction;
}

class LayerAction : public QWidget
{
    Q_OBJECT

public:
    explicit LayerAction(QWidget *parent = nullptr);
    ~LayerAction();

public slots:
    void setTarget(QString sObjPath);

private:
    Ui::LayerAction *ui;

    enum RB{_NONE=0,_PAGE,_PAGE_NO_STOP,_POP,_CHANGE,_GPIO,_SCRIPT};

    QStringList m_listKeyMapping;

    QButtonGroup m_buttonRb;


    QString m_sObjPath;


    QString m_sLayerName;


    QString m_sObjName;


    ObjData *m_obj =nullptr;

    void refresh();


    void writeData();

    int m_iCurrentIdx = 0;

    bool m_bLockSend = false;

private slots:

    void slotRbClicked(int iId);
    void on_cbChangeLayer_currentIndexChanged(int index);
    void on_cbChangeObj_currentIndexChanged(int index);
    void on_txScript_textEdited(const QString &arg1);
    void on_sbGpioPin_valueChanged(int arg1);
    void on_sbGpioValue_valueChanged(int arg1);
    void on_cbLayer_currentIndexChanged(int index);
};

#endif // LAYERACTION_H
