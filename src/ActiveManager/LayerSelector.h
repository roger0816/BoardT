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
#include <QRadioButton>
#include <QSettings>

class LayerSelector : public QWidget
{
    Q_OBJECT
public:
    explicit LayerSelector(QWidget *parent = nullptr);

    void setData(QMap<QString , QPixmap> dData,QString sPath);


signals:

    void sendSelectLayer(QString sName);

private:

    QString m_sPath;

    QHBoxLayout *m_lay;

    QList<QPushButton*> m_listBtn;

   // QList<QLabel*> m_listLb;

    QList<QRadioButton*> m_listRadioBtn;

    void resizeEvent(QResizeEvent *) override;

    void showEvent(QShowEvent *) override;
    void setUiRect();


private slots:

    void slotClicked();

    void slotClickedRadio();

};

#endif // LAYERSELECTOR_H
