#ifndef DIALOGPAINTER_H
#define DIALOGPAINTER_H

#include <QWidget>
#include <QDialog>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPixmap>
#include <QPoint>
#include <QPointF>
#include <QShowEvent>
#include <QResizeEvent>
#include <QButtonGroup>
#include <QDebug>

namespace Ui {
class DialogPainter;
}

class CPainter :public QWidget
{
    Q_OBJECT
public:
    explicit CPainter(QWidget *parent =nullptr);
    ~CPainter();

    void setRgb(int r,int g,int b);

    void setPwidth(int i );

       QPixmap pix;

protected:
   void paintEvent(QPaintEvent *);
   void mouseReleaseEvent(QMouseEvent *);
   void mousePressEvent(QMouseEvent *);
   void mouseMoveEvent(QMouseEvent *);
   void showEvent(QShowEvent * );

   void resizeEvent(QResizeEvent *);


   QPoint lastPoint;
   QPoint endPoint;

    QColor m_color;

    int m_iPsize = 2;
};

class DialogPainter : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPainter(QWidget *parent = nullptr);
    ~DialogPainter();

    QButtonGroup m_btns;

    QString m_sSavePath="";


private:
    Ui::DialogPainter *ui;

private slots:
    void colorClicked();

    void sizeClicked();
    void on_btnCancel_clicked();
    void on_btnSend_clicked();
};

#endif // DIALOGPAINTER_H
