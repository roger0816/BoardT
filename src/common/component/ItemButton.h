#ifndef ITEMBUTTON_H
#define ITEMBUTTON_H

#include <QWidget>
#include "ItemBase.h"

class ItemButton : public ItemBase
{
    Q_OBJECT
public:
    explicit ItemButton(QWidget *parent = nullptr);

    QPushButton *m_btn;

    void showEvent(QShowEvent *) override;

    bool init() override;


    QMap<QString ,int> m_gpio;


signals:

public slots:

    void clicked();
};

#endif // ITEMBUTTON_H
