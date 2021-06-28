#ifndef EDITFUNC_H
#define EDITFUNC_H

#include <QObject>
#include <QPushButton>
#include "cData/ObjData.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QCheckBox>

class EditFunc : public QObject
{
    Q_OBJECT
public:
    explicit EditFunc(QObject *parent = nullptr);

    bool setColor(ObjData *obj,QString sDataKey, QPushButton*btn =nullptr );

    bool setColor(QColor current, QVariant &var);

    void setFont(ObjData *obj,QString sDataKey, QPushButton*btn);

    bool setFont(QFont &current);

    void setCent(ObjData *obj,QString sDataKey, QCheckBox *btn);



    void setBgImage(ObjData *obj, QString sTitle, QString sDataKey);

    void clearBgImage(ObjData *obj, QString sDataKey);
signals:

};

#endif // EDITFUNC_H
