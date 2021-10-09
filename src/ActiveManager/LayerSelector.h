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
#include <QDateTime>
#include <QButtonGroup>


class LayerSelector : public QWidget
{
    Q_OBJECT
public:
    explicit LayerSelector(QWidget *parent = nullptr);

    void setData(QMap<QString , QPixmap> dData,QString sPath);

    void toDef();

    //edit select focus
    QString m_sCurrentPath="";

    //defult layer select
    QString m_sSetTargetPath = "def";
signals:

    void sendSelectLayer(QString sName);

private:

    QString m_sPath;


    QList<QPushButton*> m_listBtn;

   // QList<QLabel*> m_listLb;

    QList<QRadioButton*> m_listRadioBtn;


    void resizeEvent(QResizeEvent *) override;

    void showEvent(QShowEvent *) override;
    void setUiRect();

    void setIdx(int iIdx);

private slots:

    void slotClicked();

    void slotClickedRadio();


};

#endif // LAYERSELECTOR_H
