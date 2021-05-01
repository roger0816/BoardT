#ifndef LAYERADDCOMPONT_H
#define LAYERADDCOMPONT_H

#include <QWidget>

namespace Ui {
class LayerAddCompont;
}

class LayerAddCompont : public QWidget
{
    Q_OBJECT

public:
    explicit LayerAddCompont(QWidget *parent = nullptr);
    ~LayerAddCompont();

private:
    Ui::LayerAddCompont *ui;
};

#endif // LAYERADDCOMPONT_H
