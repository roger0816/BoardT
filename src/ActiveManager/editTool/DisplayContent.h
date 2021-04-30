#ifndef DISPLAYCONTENT_H
#define DISPLAYCONTENT_H

#include <QWidget>
#include <QDebug>
#include <QSettings>
#include <QDir>
#include <QResizeEvent>
#include "CData.h"
#include "ItemContent.h"
namespace Ui {
class DisplayContent;
}

class DisplayContent : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayContent(QWidget *parent = nullptr);
    ~DisplayContent();


    QString setNewContent(QString sType);

    void setBgImage(QString sPath);

    bool checkNewName(QString sName);

    QList<ItemContent*> m_listItem;

    ItemContent * m_currentItem = nullptr;

    void setTypeMapping(QString sFile);


    QMap<QString,int> m_dDefine;

    QString currentItemType();

    void saveFile(QString sPath);

    void loadFile(QString sPath);

    void clearUi();

    void setTxData(DataText txData, int iIdx=-1);

    void rename(QString sName);

    void resizeEvent(QResizeEvent *) override;

    float m_fDiffSize =0.500;
private:
    Ui::DisplayContent *ui;

    QString m_sBgPath="";

    QString m_sPath="";
signals:


    void sendItemUpdate();

public slots:

    void slotItemChange();

    void slotFocus();

};

#endif // DISPLAYCONTENT_H
