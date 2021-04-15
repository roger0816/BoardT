#ifndef LAYERCONTENT_H
#define LAYERCONTENT_H

#include <QWidget>
#include "ItemVideo.h"
#include "ItemMediaCent.h"
#include "Global.h"
#include <QDesktopWidget>

namespace Ui {
class LayerContent;
}

class LayerContent : public QWidget
{
    Q_OBJECT

public:
    explicit LayerContent(QWidget *parent = nullptr);
    ~LayerContent();

    void setPath(QString sPath,QMap<QString,int> typeMapping);

   // int m_iType;

    QString m_sType;

    ItemMediaCent *m_mdeia = nullptr;

    ItemVideo *m_video = nullptr;

    void resizeEvent(QResizeEvent *) override;

    void showEvent(QShowEvent *) override;

    void checkLayout(int &iX,int &iY,int &iW,int &iH);

    void stopVideo();
private:
    Ui::LayerContent *ui;


};

#endif // LAYERCONTENT_H
