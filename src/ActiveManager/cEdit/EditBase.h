#ifndef EDITBASE_H
#define EDITBASE_H

#include <QObject>
#include <QPushButton>
#include "cData/ObjData.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QCheckBox>
#include <QWidget>

class EditBase : public QWidget
{
    Q_OBJECT
public:
    explicit EditBase(QWidget *parent = nullptr);

protected:
    bool setEditColor(ObjData *obj,QString sDataKey, QPushButton*btn =nullptr );

    bool setEditColor(QColor current, QVariant &var);

    void setEditFont(ObjData *obj,QString sDataKey, QPushButton*btn);

    bool setEditFont(QFont &current);

    void setEditCent(ObjData *obj,QString sDataKey, QCheckBox *btn);

    void setEditBgImage(ObjData *obj, QString sTitle, QString sDataKey);

    void clearEditBgImage(ObjData *obj, QString sDataKey);

signals:

};

#endif // EDITBASE_H
