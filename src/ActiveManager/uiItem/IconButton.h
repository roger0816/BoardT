#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QShowEvent>
#include <QFocusEvent>
#include <QEvent>

namespace Ui {
class IconButton;
}

class IconButton : public QWidget
{
    Q_OBJECT

public:
    explicit IconButton(QWidget *parent = nullptr);
    ~IconButton();

    void setData(QStringList listRes,QString sText);

    void setText(QString sText);
 private:
    void mouseMoveEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

    void enterEvent(QEvent *event) override;

    void leaveEvent(QEvent *event) override;


    void showEvent(QShowEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

    void reSet(int i=-1);



    int m_iStatus;

    QString m_sResBase;

    QString m_sResFocus;

    QString m_sResClick;

signals:
    void clicked();


private:
    Ui::IconButton *ui;
};

#endif // ICONBUTTON_H
