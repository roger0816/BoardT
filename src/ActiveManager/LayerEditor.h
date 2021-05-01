#ifndef LAYEREDITOR_H
#define LAYEREDITOR_H

#include <QWidget>
#include "CData.h"
#include "ObjData.h"
#include <QFileDialog>
#include <QFontDialog>

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
    void on_btnTxtColor_clicked();

    void on_btnBgColor_clicked();




    void on_sbX_valueChanged(int);

    void on_sbY_valueChanged(int );

    void on_sbW_valueChanged(int );

    void on_sbH_valueChanged(int );

    void on_txtText_textChanged(const QString &);

    void on_spSize_valueChanged(int );

    void on_chCent_clicked();

    void on_btnToTop_clicked();

    void on_btnRename_clicked();

    void on_btnBgImage_clicked();

    void on_btnCmd_clicked();

    void on_txtBgImage_textChanged(const QString &arg1);

    void on_btnClearBg_clicked();

    void on_btnSelectFont_clicked();

private:
    Ui::LayerEditor *ui;

    QString m_sPath;

    bool m_bFristBgColor = true;

    bool m_bFristTxColor = true;

    ObjData *m_obj =nullptr;

    void readyCallUpdate();

    bool m_bLockCallUpdate = false;


signals:
    void callUpdate();

    void callRaise(QString objPath);

    void callRename(QString sOldPath,QString sNewPash);
};

#endif // LAYEREDITOR_H
