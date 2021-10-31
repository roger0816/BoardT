#ifndef ITEMLABEL_H
#define ITEMLABEL_H

#include <QWidget>
#include "ItemBaseObj.h"
#include <QLabel>




namespace Ui {
class ItemLabel;
}

class ItemLabel : public ItemBaseObj
{
    Q_OBJECT

public:
    explicit ItemLabel(QWidget *parent = nullptr);
    ~ItemLabel();

    void init() override;

    void updateItem()override;

    virtual void setLbStyle(QString sTxtColorKey,QString sBgColorKey,QString sImagePathKey,QString sFontKey,QString sCentKey);

    QLabel *m_lb;
private:
    Ui::ItemLabel *ui;

   // DataText m_data;
};

#endif // ITEMLABEL_H
