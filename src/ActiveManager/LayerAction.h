#ifndef LAYERACTION_H
#define LAYERACTION_H

#include <QWidget>

namespace Ui {
class LayerAction;
}

class LayerAction : public QWidget
{
    Q_OBJECT

public:
    explicit LayerAction(QWidget *parent = nullptr);
    ~LayerAction();

private:
    Ui::LayerAction *ui;
};

#endif // LAYERACTION_H
