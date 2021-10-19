#ifndef LAYEREDITGRID_H
#define LAYEREDITGRID_H

#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QShowEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QGridLayout>


class TouchLabel : public QWidget
{
    Q_OBJECT
public:
    TouchLabel(QWidget *parent =nullptr);

    void setPic(QString sFile);

    void setClicked(bool bIsClicked);

signals:

    void clicked();

private:

    bool m_bIsSelect = false;

    QPushButton *m_btn;

    QLabel *m_lb;

    void resetSize();

    void showEvent(QShowEvent * ) override;

    void resizeEvent(QResizeEvent *) override;

private slots:
    void slotClicked();

};

namespace Ui {
class LayerEditGrid;
}

class LayerEditGrid : public QWidget
{
    Q_OBJECT

public:
    explicit LayerEditGrid(QWidget *parent = nullptr);
    ~LayerEditGrid();

    void set4Grid(bool b);

    bool m_bIs4Grid = true;

    void showEvent(QShowEvent* ) override;

    void resizeEvent(QResizeEvent *) override;

    void resetSize();

    QList<TouchLabel*> m_listItem;

    QGridLayout *lay ;


private:
    Ui::LayerEditGrid *ui;
};

#endif // LAYEREDITGRID_H
