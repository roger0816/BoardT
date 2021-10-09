#ifndef STAGEEDITAREA_H
#define STAGEEDITAREA_H

#include <QWidget>
#include <QDebug>
#include <QShowEvent>

namespace Ui {
class StageEditArea;
}

class StageEditArea : public QWidget
{
    Q_OBJECT

public:
    explicit StageEditArea(QWidget *parent = nullptr);
    ~StageEditArea();

private slots:
    void on_btnBack_clicked();

private:
    Ui::StageEditArea *ui;

    void refreshSelector(bool bToDef = false);

    void showEvent(QShowEvent *event) override;

signals:
    void sendBack();

};

#endif // STAGEEDITAREA_H
