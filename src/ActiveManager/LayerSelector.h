#ifndef LAYERSELECTOR_H
#define LAYERSELECTOR_H

#include <QWidget>
#include <QDebug>
#include <QHBoxLayout>
#include <QPushButton>
#include <QIcon>
#include <QResizeEvent>
#include <QShowEvent>
#include <QLabel>

class LayerSelector : public QWidget
{
    Q_OBJECT
public:
    explicit LayerSelector(QWidget *parent = nullptr);

    void setData(QMap<QString , QPixmap> dData);
signals:

    void sendSelectLayer(QString sName);

private:

    QHBoxLayout *m_lay;

    QList<QPushButton*> m_listBtn;

    QList<QLabel*> m_listLb;

    void resizeEvent(QResizeEvent *) override;

    void showEvent(QShowEvent *) override;
    void setUiRect();

private slots:

    void slotClicked();

};

#endif // LAYERSELECTOR_H
