#ifndef LAYEREDITOR_H
#define LAYEREDITOR_H

#include <QWidget>
#include "CData.h"
#include <QColorDialog>
#include "ObjData.h"
#include <QFileDialog>
#include <QFontDialog>
#include "DialogMsg.h"
#include <QDebug>
#include <QLineEdit>
#include "DialogSelectFile.h"

#include "Voj.h"

namespace Ui {
class LayerEditor;
}

class LayerEditor : public QWidget
{
    Q_OBJECT

public:
    explicit LayerEditor(QWidget *parent = nullptr);
    ~LayerEditor();
public slots:
    void setTarget(QString sObjPath);

    void refresh();

private slots:

    void on_sbX_valueChanged(int);

    void on_sbY_valueChanged(int );

    void on_sbW_valueChanged(int );

    void on_sbH_valueChanged(int );

    void on_btnToTop_clicked();

    void on_btnRename_clicked();

    void on_btnDelete_clicked();




    //



private:
    Ui::LayerEditor *ui;

    QString m_sPath;

    QString m_sLayerName;

    QString m_sObjName;

    bool m_bFristBgColor = true;

    bool m_bFristTxColor = true;

    ObjData *m_obj =nullptr;

    void updateRect();

    bool m_bLockCallUpdate = false;

    bool deleteDirectory(const QString &path);

   // QList<QLineEdit*> m_listMar;



signals:
    void callUpdate();

    void callRaise(QString objPath);

    void callRename(QString sOldPath,QString sNewPash);

    void callDelete(QString sPath);



private slots:


    void on_txQr_textChanged(const QString &arg1);


    //tx value



    void on_txUrl_textChanged(const QString &arg1);
};

#endif // LAYEREDITOR_H
