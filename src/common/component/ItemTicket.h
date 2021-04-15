#ifndef ITEMTICKET_H
#define ITEMTICKET_H

#include <QWidget>
#include "ItemBase.h"
#include "Global.h"


namespace Ui {
class ItemTicket;
}

class ItemTicket : public ItemBase
{
    Q_OBJECT

public:
    explicit ItemTicket(QWidget *parent = nullptr);
    ~ItemTicket();

    bool init() override;

    void resizeEvent(QResizeEvent *) override;

    void mousePressEvent(QMouseEvent *) override;

    void timerEvent(QTimerEvent *) override;

private slots:

    void clickSelect();

    void on_btnPreQeust_clicked();

    void on_btnNextQuest_clicked();

private:
    Ui::ItemTicket *ui;

    QStringList m_listInfo;

    QStringList m_listQuest;

    int m_iChangeTime=5;

    int m_iInfoIdx = 0;

    int m_iQuest = 0;

    QList<QPushButton*> m_listSelectBtn;

    void setQuest();

    void setSelectButton();

    bool checkFile(QString sFile);

   // QList<QStringList> m_listSelectPath;
};

#endif // ITEMTICKET_H
