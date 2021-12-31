#ifndef ITEMTIMESCHEDULE_H
#define ITEMTIMESCHEDULE_H

#include <QWidget>


class ItemWidgetClick :public QWidget
{
    Q_OBJECT
public:
  void setFocus(bool b);

};


namespace Ui {
class ItemTimeSchedule;
}

class ItemTimeSchedule : public QWidget
{
    Q_OBJECT

public:
    explicit ItemTimeSchedule(QWidget *parent = nullptr);
    ~ItemTimeSchedule();

private:
    Ui::ItemTimeSchedule *ui;
};

#endif // ITEMTIMESCHEDULE_H
