#ifndef VOJ_H
#define VOJ_H

#include <QColorDialog>
#include <QList>
#include <QString>
#include <QColor>
#include <QDebug>
#include <QFileInfoList>
#include <QFileInfo>
#include <QSettings>
#include <QDir>
#include <QFont>


static QString E_TEXT = "text";

static QString E_PIC= "pic";

static QString E_BUTTON ="button";

static QString E_DATETIME ="dateTime";

static QString E_WEB ="web";

static QString E_FUNCTION ="function";

static QString E_VIDEO ="video";

struct DataText
{
    QString sText="Label";

    int iPixSize=32;

    QFont font;

    bool bIsCent=true;

    QColor textColor = QColor(0,0,0,255);

    QColor bgColor = QColor(255,255,255,255);

    QString m_sImagePath;

    QString m_sCmdPath;


};


#endif // VOJ_H
